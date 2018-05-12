---
title: Record some java Function when I code on Leetcode
date: 2018-05-11 14:28:25
categories:
tags:
---
*****

# HashMap相关
## 常用函数说明
## 如何在Hashmap中插入相同的key值
要在HashMap中插入重复的值，首先需要弄清楚HashMap里面是怎么存放元素的。   
**put方法**: Map里面存放的每一个元素都是key-value这样的键值对，而且都是通过put方法进行添加的，而且相同的key在Map中只会有一个与之关联的value存在。put方法在Map中的定义如下。

`put(K key, V value);`  
> put()方法实现：首先hash(key)得到key的hashcode()，hashmap根据获得的hashcode找到要插入的位置所在的链，在这个链里面放的都是hashcode相同的Entry键值对，在找到这个链之后，会通过equals()方法判断是否已经存在要插入的键值对，而这个equals比较的其实就是key。  

<!-- more -->
```
public V put(K key,V value)
Parameters:
key - key with which the specified value is to be associated
value - value to be associated with the specified key
Return: the previous value associated with
key, or null if there was no mapping for key. 
```
它用来存放key-value这样的一个键值对，返回值是key在Map中存放的旧value，如果之前不存在则返回null。HashMap的put方法是这样实现的。
```java
public V put(K key, V value) {
    if (key == null)
        return putForNullKey(value);
    int hash = hash(key);
    for (Entry<K,V> e = table[i]; e != null; e = e.next) {
        Object k;
        if (e.hash == hash && ((k = e.key) == key || key.equals(k))) {
            V oldValue = e.value;
            e.value = value;
            e.recordAccess(this);
            return oldValue;
        }
    }

    modCount++;
    addEntry(hash, key, value, i);
    return null;
}
```
从上我们可以看到在添加对应的key-value这样的组合时，如果原本已经存在对应的key，则直接改变对应的value，并返回旧的value，而在判断key是否存在的时候是先比较key的hashCode，再比较相等或equals的。 
直接从上面代码来看是比较的对应Map.Entry的hashCode和key的hashCode，而实际上Map.Entry的hashCode其实就是其存放key的hashCode。而如果对应的key原本不存在的话将调用addEntry将对应的key-value添加到Map中。addEntry传递的参数hash就是对应key的hashCode。 
实现添加重复元素 
通过对put()方法的研究，我们可以发现，判断key是否存在的时候是先比较key的hashCode，再比较相等或equals的，所以重写hashCode()和equals()方法即可实现添加重复元素。
```java
@Override
public int hashCode(){                 
     return this.arga.hashCode() * this.argb.hashCode() ; 
} 

@Override
public boolean equals(Object obj) {   
    if (this == obj) {               
        return true;                  
    }         
    if (!(obj instanceof MyType)) {  
        return false;               
    }    
    MyType p = (MyType) obj;  
    if (this.arga.equals(p.arga) && this.argb.equals(p.argb)) {              
        return true ;                  
    } else {           
        return false ;                
    }       
}
```
重写这两个方法之后就可以覆盖重复的键值对，如果需要对value进行叠加，调用put()方法之前用containsKey()方法判断是否有重复的键值，如果有，则用get()方法获取原有的value，再加上新加入的value即可。