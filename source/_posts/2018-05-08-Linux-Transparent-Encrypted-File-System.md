---
title: Linux透明加密文件系统1_代码分析
date: 2018-05-08 14:12:25
categories: Linux File System
tags: Linux
---
# Linux透明加密文件系统代码分析
主要分为三个部分：
> 第一部分是交互脚本与自动化脚本(Ubuntu)  
> 第二部分是界面设计  
> 第三部分是开源项目代码的说明  

用户使用的是基于QT的用户界面，可以选择需要加密的文件路径，已经加密之后的路径。当图形界面接收到这些信息之后，会将该信息转换成一段包含了8个参数的数据包传递给shell脚本进行处理。
<!-- more -->
## 一.交互脚本与自动化脚本
### 1. 处理交互式过程的脚本
```sh
#!/usr/bin/expect
#该文件是处理交互式过程的主要文件，用来对输出信息进行解析，并自动输入对应的信息
set timeout 2
set ecryptfs_real [lindex $argv 0]
#真实文件路径,实际的加密文件位置
set ecryptfs_mount [lindex $argv 1]
#挂载点路径，解密文件的位置
set tangpassword [lindex $argv 2]
#用户密码
set key_type1 [lindex $argv 3]
 #密码管理方式
set Passphrase [lindex $argv 4]
 #文件加密密码
set ecryptfs_type [lindex $argv 5]
#文件加密类型
set key_bytes [lindex $argv 6]
#文件加密位数
set ecryptfs_fspath [lindex $argv 7]
#路径是否加密
set ecryptfs_filename [lindex $argv 8]
#文件名是否加密
spawn sudo mount -t ecryptfs $ecryptfs_real $ecryptfs_mount#挂载加密文件系统
expect "password for tang:"
send "$tangpassword\n"
#填充用户密码
expect "Select key type to use for newly created files:"
send "$key_type1\n"
expect
#填充加密方式类型 "Passphrase:"
send "$Passphrase\n"
#填充文件加密密码
expect "aes"
send "$ecryptfs_type\n"
#填充文件加密类型
expect "Select key bytes:"
send "$key_bytes\n"
#填写文件加密位数
expect "Enable plaintext passthrough"
send "$ecryptfs_fspath\n"
#选择是否对路径加密
expect "Enable filename encryption"
send "$ecryptfs_filename\r"
interact
#选择是否对文件名加密
#expect eof
#exit
```

### 2. 与QT交互的脚本

```sh
#!/bin/bash
##该脚本主要作用是接收QT传递过来的变量，并进行解析，之后，调用相应的交互处理脚本##接收QT传递过来的变量
ECRYPTFS_REAL=$1	                ##获取加密路径
PASSWD=$2		##用户密码
PASS_TYPE=$3		##密码类型
PASSPHRASE=$4		##加密路径，挂载点
ECRYPTFS_TYPE=$5	                ##加密类型
ECRYPTFS_BIT=$6		##加密位数
ECRYPTFS_FS=$7		##路径是否加密
ECRYPTFS_FILENAME=$8         ##文件名是否加密
count=0   ##初始值
dir="/tmp/mnt/ecryptfs$count" ##初始挂载点
echo "Ecryptfs加密程序启动中..."
echo "申请超级用户权限,请输入用户密码"
##/bin/testpass
df 1>/tmp/1.txt 2>/dev/null
##检测当前已经使用的挂载点，建立一个新的挂载点来使用
echo "已经挂载的加密目录有："
 while cat /tmp/1.txt | grep -q $dir 2>/dev/null
   ##挂载点 是否使用了
do
echo $dir
let count=$count+1 ##一定要是/bin/bash如是/bin/sh这里就会出错
dir="/tmp/mnt/ecryptfs$count"  ###新挂载点
done
rm /tmp/1.txt
echo "新增挂载目录：" ###创建新的挂载点
if [ ! -d $dir ];then ##判断目录是否存在
mkdir -p $dir ###建立新挂载点目录,选项p，可以创建连续文件夹
fi
    echo "加密程序启动，开始加密……
 echo "请输入加密密码，选择加密方式："

## sudo mount -t ecryptfs $(pwd) $dir  ### $( )为引用命令结果
##调用交互脚本来处理和用户的交互过程
echo $ECRYPTFS_REAL $dir $PASSWD $ECRYPTFS_TYPE $ECRYPTFS_BIT $ECRYPTFS_FS $ECRYPTFS_FILENAME
   /bin/automount $ECRYPTFS_REAL $dir $PASSWD $PASS_TYPE $PASSPHRASE $ECRYPTFS_TYPE $ECRYPTFS_BIT $ECRYPTFS_FS $ECRYPTFS_FILENAME

```

### 3. 挂载点操作脚本
```sh
#!/bin/bash
##用来对当前挂载点进行卸载删除
count=0
dir="/tmp/mnt/ecryptfs$count"
gksudo df 1>/tmp/1.txt
while cat /tmp/1.txt |grep -q $dir 2>/dev/null	##检查现在存在的挂载
do
 echo $dir
let count=$count+1
sudo umount $dir && rmdir $dir　　##卸载挂载点，卸载成功的前提下删除挂载点
dir="/tmp/mnt/ecryptfs$count"
done
```

### 4. 添加到鼠标右键菜单的执行脚本
 ```sh
#!/bin/bash
##添加到右键的执行脚本，用来打开QT交互式界面，获取用户的输入信息
/home/tang/ecryptfs/imageconverter
#/bin/ecryptfs_mounted.sh&
 ```

### 5. 在QT调用执行挂载脚本
```sh
 #!/bin/bash
##在QT中调用该脚本，该脚本的主要功能是执行挂载脚本ecryptfs_mounted.sh
REALFILE=$1
ECRYPTFSPATH="/bin/ecryptfs_mounted.sh $REALFILE"
echo $REALFILE 1>/TMP/2.txt
echo
$ECRYPTFSPATH 1>>/tmp/2.txt
exec
$ECRYPTFSPATH
#exec gnome-terminal -x
$ECRYPTFSPATH
#/bin/ecryptfs_mounted.sh&
```

## 二. ＱＴ界面程序设计
```c++
#include <QtGui>
#include "convertdialog.h"

ConvertDialog::ConvertDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);      //创建并布局好所有的窗口部件
     passwordEdit->setEchoMode (QLineEdit::Password);//用户口令输入框
    filepasswordEdit->setEchoMode (QLineEdit::Password);//文件密码输入框
}

void ConvertDialog::on_browseButton_clicked()//选择路径按钮触发
{
    QString initialName = sourceFileEdit->text();//加密文件夹路径输入框
    if (initialName.isEmpty())
        initialName = QDir::homePath();//为空，使用默认路径
    QString fileName =
            QFileDialog::getExistingDirectory(this, tr("Choose File"),
                                         initialName);//弹出计算机路径选择框，选择路径加密
    fileName = QDir::toNativeSeparators(fileName);//加密路径
    if (!fileName.isEmpty()) {
        sourceFileEdit->setText(fileName);//将路径信息保存起来
       // buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
}

void ConvertDialog::on_passwordEdit_textEdited(const QString &arg1)//password密码框
{
    QRegExp regx ("^[^ ]+$");// 设定正则表达式，不能输入空格
    QValidator *validator=new QRegExpValidator(regx,this);
    passwordEdit->setValidator(validator);
    filepasswordEdit->setValidator(validator);//正则表达式控制输入框字符格式
}

void ConvertDialog::on_filepasswordEdit_textEdited(const QString &arg1)//filepassword密码框
{
    QRegExp regx ("^[^ ]+$");// 不能输入空格
    QValidator *validator2=new QRegExpValidator(regx,this);
    passwordEdit->setValidator(validator2);
    filepasswordEdit->setValidator(validator2);//正则表达式控制输入框字符格式
    }

void ConvertDialog::on_shellButton_clicked()//确定加密按钮触发
{
    //system("/bin/ecryptfs_mounted.sh /home/tang/");  //直接调用的方式，会阻塞进程
    //QProcess::execute("/opt/run")　　//调用QT里面的函数来实现，会阻塞进程

    passwordEdit->setInputMask("");//提取password输入框内容
    filepasswordEdit->setInputMask("");//提取filepassword输入框内容

    if(sourceFileEdit->text().isEmpty()) //  必须输入加密路径，否则报错
    {
         QMessageBox::warning(this,tr("worning"),tr(" Please select the path to encrypt !"),QMessageBox::Yes);//报错信息
          sourceFileEdit->setFocus();//移动光标到加密路径输入框
    }

    else if(passwordEdit->text().isEmpty()||filepasswordEdit->text().isEmpty())//如果任一密码为空，直接报错
    {
        QMessageBox::warning(this,tr("worning"),tr(" user password or file password can't be empty!"),QMessageBox::Yes);
        //报错信息
       passwordEdit->clear();//清空用户密码输入框
       filepasswordEdit->clear();//清空文件密码输入框
       passwordEdit->setFocus();//移动光标到用户密码输入框
    }
     else
    {
    QString p1=passwordEdit->text().trimmed();//去除首尾空格
    QString f1=filepasswordEdit->text().trimmed();// 去除首尾空格

    QString p2,f2;
    int length1=p1.length();
    int length2=f1.length();
    for (int i=0;i<length1;i++)
    {if (p1[i]!=' ') p2+=p1[i];}//去除password中的空格

    for (int i=0;i<length2;i++)
    {if (f1[i]!=' ') f2+=f1[i];}//去除filepassword中的空格

    QString define = p2+" "+"1 "+f2+" "+ecryptfstypeComboBox->currentText().toLower()
                    +" "+ecryptfsbitComboBox->currentText().toLower()
                    +" "+fileecryptfsComboBox->currentText().toLower()
                    +" "+filenameecryptfsComboBox->currentText().toLower();//输出需要的信息
    qDebug()<<define;
    QString ecryptfs_sh = sourceFileEdit->text()+" "+define;//写出保存的信息
    //ecryptfs_sh.insert(0,QString("/bin/tangguoze "));
    qDebug()<<ecryptfs_sh;
    QStringList arguments;
    arguments << ecryptfs_sh;//输出信息到脚本中
    QProcess *poc = new QProcess;//定义新进程
    poc -> start ("/bin/tangguoze",arguments);//在QT中调用启动进程运行
    }
}
```

## 三．eCryptfs开源部分的分析
主要分为7个部分：
1. keystore  
Keystore部件从文件中提供文件头信息，并将信息数据转发给callout应用程序。Keystore与callout应用程序之前使用netlink机制通信，通信的发起者为keystore。

2. Callout应用程序  
Callout应用程序根据目标策略对头文件信息作出评估，并给出各种操作，如：调用后台给应用程序弹出对话框要求密码短语，或用私钥解密一个会话秘钥。  
eCryptfs内核模块和用户空间秘钥管理代码之间的主要通信是请求秘钥，由内核秘钥环发起。Callout应用程序从目录分析策略信息，解析每个文件的头信息。为了满足挂起的公钥请求，他可以调用PKI API，或者用特殊的签名搜索带盐值得密码短语。  
3. eCryptfs后台弹出对话框输入密码短语  
为了能给用户弹出对话框来输入密码短语，eCryptfs必须提供得到X会话的通道。这可能通过运行一个后台来实现。eCryptfs后台侦听一个socket，它的地址信息写在用户的会话秘钥环中，无论何时策略需要弹出一个对话框请求密码短语时，callout应用程序都能提取socket的地址信息，并用它请求后台给用户弹出对话框，接着，后台将用户的密码短语返回给callout应用程序。  

4. 内核秘钥环  
内核秘钥环用于管理和保护秘钥和认证特征。eCryptfs用内核秘钥环存储认证特征、节点加密统计信息和秘钥。  
5. PAM  
PAM（可插入的认证模块）提供了灵活的认证机制。eCryptfs含有一个模块，能捕获用户注册的密码短语，并将它放在用户的会话秘钥环中，这个密码短语作为无盐值密码短语认证特征。
eCryptfs可以基于策略，使用这个密码短语进行加密操作。如：用这个密码短语从用户的GunPG秘钥环中提取他的私钥；通过字符串到秘钥操作，将这个密码短语直接用于保护文件的会话秘钥；这个秘钥短语还可以与存在TPM中的秘钥结合在一起，用来提供两个因子的认证，即用户为了访问一个文件，他必须注册到特殊主机，还需要使用特征的密码短语。  

6. 公钥设施  
eCryptfs提供了可插入的PKI（公钥设施）接口，eCryptfs的PKI模块利用GPGME（GuuPG Made Easy）接口访问用户的GnuPG秘钥环。这个模块能使用用户的注册密码解密用户保存的私钥。  
eCryptfs的TMP PKI模块的TrouSerS使用接口与TPM（可信平台模块）通信，用来使用存在硬件中的私钥，将文件绑定到一个特定的主机上。
eCryptfs openCryptoki PKCS#11框架PKI通过各种open Crytok的硬件设备，对在硬件上执行公钥操作的机制提供了支持。  
7. 目标中心策略（Target-centric Polocies）  
当应用程序创建一个新文件时，eCryptfs必须作出许多的决策，如：文件是否加密？用哪个对称密码加密数据？文件是否加入HMAC并附加IV？会话秘钥长度是多少？如何保护会话秘钥？等等。
eCryptfs将策略定义文件应用于目标。  
eCryptfs文件系统由内核空间系统和用户空间系统两部分组成。内核空间系统由内核空间的内核keystore、内核加密API、eCryptfs层、加密元数据和底层文件系统组成。而用户空间由callout应用程序，eCryptfs后台和PKI API等组成。  
另外，eCryptfs文件系统使用了Linux内核的密钥环服务、Linux可插入认证模块(Pluggable Authentication Modules, PAM)、可信平台模块（Trusten Platform Module, TPM）和GnuPG密钥环，Ecryptfs超级块私有数据主要包括加密的各种信息，如：认证特征、密钥环等。  

<pre>
/* superblock private data. */
struct ecryptfs_sb_info {
	struct super_block *wsi_sb;
	struct ecryptfs_mount_crypt_stat mount_crypt_stat;
};

/* dentry private data. Each dentry must keep track of a lower
 * vfsmount too. */
struct ecryptfs_dentry_info {
	struct path lower_path;
	struct ecryptfs_crypt_stat *crypt_stat;
};

/* inode private data. */
struct ecryptfs_inode_info {
	struct inode vfs_inode;
	struct inode *wii_inode;
	struct file *lower_file;
	struct mutex lower_file_mutex;
	struct ecryptfs_crypt_stat crypt_stat;
};

/* file private data. */
struct ecryptfs_file_info {
	struct file *wfi_file;
	struct ecryptfs_crypt_stat *crypt_stat;
};

eCryptfs的认证特征包括会话密钥、口令和私钥等以及他们的签名。会话密钥将口令进行加密。结构eCryptfs_auth_toke存放了eCryptfs文件系统范围内的的认证特征。
/* May be a password or a private key */
struct ecryptfs_auth_tok {
	u16 version; /* 8-bit major and 8-bit minor */
	u16 token_type;
#define ECRYPTFS_ENCRYPT_ONLY 0x00000001
	u32 flags;
	struct ecryptfs_session_key session_key;
	u8 reserved[32];
	union {
		struct ecryptfs_password password;
		struct ecryptfs_private_key private_key;
	} token;
} __attribute__ ((packed));

加密统计信息结构ecryptfs_crypt_stat存入了与每个加密文件相关的加密信息。如：文件的加密操作标识、文件头的结构信息等。列出如下：
/**
 * This is the primary struct associated with each encrypted file.
 *
 * TODO: cache align/pack?
 */
struct ecryptfs_crypt_stat {
#define ECRYPTFS_STRUCT_INITIALIZED 0x00000001
#define ECRYPTFS_POLICY_APPLIED     0x00000002
#define ECRYPTFS_NEW_FILE           0x00000004
#define ECRYPTFS_ENCRYPTED          0x00000008
#define ECRYPTFS_SECURITY_WARNING   0x00000010
#define ECRYPTFS_ENABLE_HMAC        0x00000020
#define ECRYPTFS_ENCRYPT_IV_PAGES   0x00000040
#define ECRYPTFS_KEY_VALID          0x00000080
#define ECRYPTFS_METADATA_IN_XATTR  0x00000100
#define ECRYPTFS_VIEW_AS_ENCRYPTED  0x00000200
#define ECRYPTFS_KEY_SET            0x00000400
	u32 flags;
	unsigned int file_version;
	size_t iv_bytes;
	size_t num_header_bytes_at_front;
	size_t extent_size; /* Data extent size; default is 4096 */
	size_t key_size;
	size_t extent_shift;
	unsigned int extent_mask;
	struct ecryptfs_mount_crypt_stat *mount_crypt_stat;
	struct crypto_blkcipher *tfm;
	struct crypto_hash *hash_tfm; /* Crypto context for generating
				       * the initialization vectors */
	unsigned char cipher[ECRYPTFS_MAX_CIPHER_NAME_SIZE];
	unsigned char key[ECRYPTFS_MAX_KEY_BYTES];
	unsigned char root_iv[ECRYPTFS_MAX_IV_BYTES];
	struct list_head keysig_list;
	struct mutex keysig_list_mutex;
	struct mutex cs_tfm_mutex;
	struct mutex cs_hash_tfm_mutex;
	struct mutex cs_mutex;
};
</pre>
