---
title: Cloud Computing Introduce
date: 2018-08-27 10:14:31
categories: Courses
tags: Cloud Computing
---

# Introduce
## What is the Cloud Computing?
Cloud computing is a model for enabling convenient, on-demand network access to a shared pool of configurable computing resources (e.g. networks, servers, applications, and services) that can be rapidly provisioned and released with minimal management effort or service provider interaction.

<!--more-->
## Some keywords

### Five Characteristics

**On-demand self-service**

This means provisioning or de-provisioning computing resources as needed in an automated fashion without human intervention [n. 介入；调停；妨碍]. An analogy to this is electricity as a utility where a consumer can turn on or off a switch on-demand to use as much electricity as required.

**Resource Pooling**

This means that computing resources are pooled to meet the demand of the consumers so that resources (physical or virtual) can be dynamically assigned, reassigned or de-allocated as per the requirement. Generally the consumers are not aware of the exact location of computing resources. However, they may be able to specify location (country, city, region and the like) for their need. For example, I as a consumer might want to host my services with a cloud provider that has cloud data centers within the boundaries of Australia.

**Ubiquitous[adj. 普遍存在的；无所不在的] network access**

This means that computing facilities can be accessed from anywhere over the network using any sort of thin or thick clients (for example smartphones, tablets, laptops, personal computers and so on).

**Elasticity**

Cloud computing provides an illusion of infinite computing resources to the users. In cloud models, resources can be elastically provisioned or released according to demand. 

**Measured service**

This means that consumers only pay for the computing resources they have used. This concept is similar to utilities like water or electricity.

-----

### Three main service models of cloud computing (Cloud Architecture)

**XaaS** offerings where X is Software, Hardware, Platform, Infrastructure, Data, Business etc.

**SAAS**  
Software as a service (SaaS). Applications hosted by a provider on a cloud infrastructure are accessed from thin or thick clients over the network or a program interface (for example, web services). Examples are Google Docs, IBM SmartCloud Docs, IBM SmartCloud Meetings, Saleforce.com’s CRM application and so on.


**PAAS**  
Platform as a service (PaaS). Providers deliver not only infrastructure but also middleware (databases, messaging engines and so on) and solution stacks for application build, development and deploy. IBM SmartCloud Application Services and Google App Engine are two examples of PaaS.

**IAAS**  
Infrastructure as a service (IaaS). It is the delivery of computing infrastructure as a service. IBM SmartCloud Enterprise+, SoftLayer cloud and Amazon EC2 are some examples of IaaS.

**HAAS**  
Hardware as a service (HaaS) refers to managed services or grid computing, where computing power is leased from a central provider. In each case, the HaaS model is similar to other service-based models, where users rent, rather than purchase, a provider's tech assets.

There are others services emanating from these main services. Storage as a service **(STaaS)** and communications as a service **(CaaS)** are two such variants.

### Four cloud deployment models( public/private/hybrid types of clouds)

**Public cloud**

This is where computing resources provided by a cloud provider are used by different organizations through public Internet on a **pay as you go (PAYG)** model. Cloud providers ensure some sort of separation for resources used by different organizations. This is known as multitenancy [n. 多租户技术].

**Private cloud**

This is where cloud infrastructure is solely owned by an organization and maintained either by this organization or a third party and can be located on site or off-site. Computing resources are behind the corporate firewall.

**Community cloud**

Here, cloud infrastructure is owned and shared by multiple organizations with a shared concern.

**Hybrid cloud**

It is the combination of any type of cloud model mentioned above connected by standardized or proprietary technology.


### Virtualization
**Virtualization Management** is the technology that abstracts the coupling between the hardware and operating system. It refers to the abstraction of logical resources away from their underlying physical resources in order to improve agility, flexibility, reduce costs and thus enhance busines valuse. Basically virtualizations in cloud are of different types such as server virtualization, storage virtuualization and network virtualization.

For example, a common interpretation of server virtualization is the mapping of single physical resources to multiple logical representations or partitions.

### Hypervisor
We’ve heard the term hypervisor, of course, when talking of virtualization and the Cloud.  Hypervisors allow a single set of physical hardware to host multiple virtual machines, and hold all of the necessary variables and information required to make those virtual machines work.  But what is a Hypervisor actually, what does a Hypervisor do, and how does it make the Cloud possible?  Let’s have a look:

In their simplest form, hypervisors are software, specialized firmware, or both which allow physical hardware to be shared across multiple virtual machines.  The way the hypervisor does this will vary from vendor to vendor – like ESXi from WMware or Hyper-V from Microsoft, but they all accomplish the same task.  Each takes one set of physical hardware (CPU, RAM, disk drives, peripherals, etc.) and allows it to be simultaneously used by multiple instances of Operating Systems (Windows, Linux, etc.).

There are two major classifications of hypervisors to be aware of.  Type 1 and Type 2 both do the same basic task, but the way they do it is quite different from each other.

### stateful versus stateless services
I assume you are referring to Security Groups (stateful) and Access Control Lists (stateless) in Ryan's videos. My understanding is:

Security Groups control connectivity to and from an EC2 instance or instances whereas ACLs control connectivity to and from a subnet.

Stateful = any connection inbound will also allow the response to be returned outbound without additional rules or will override an explicit DENY.

Stateless = you must explicitly ALLOW traffic in both directions.

### cloud business model

### on-premises/on-prem

On-premises software (sometimes misspelled "on-premise" or abbreviated as "on-prem") is installed and runs on computers on the premises (in the building) of the person or organization using the software, rather than at a remote facility such as a server farm or cloud. On-premises software is sometimes referred to as “shrinkwrap” software, and off-premises software is commonly called “software as a service” ("SaaS") or “cloud computing”.

### enterprise application  

Enterprise application integration is an integration framework composed of a collection of technologies and services which form a middleware or "middleware framework" to enable integration of systems and applications across an enterprise.

### pay as you go 

Pay-as-you-go cloud computing (PAYG cloud computing) is a payment method for cloud computing that charges based on usage. The practice is similar to that of utility bills, using only resources that are needed.

## Some websites links
- [AWS Training](https://www.aws.training/)  
There are some courses on this website. 

 
- AWS lab: [awsacademy.qwiklabs.com](https://awsacademy.qwiklab.com/home)

Use lab on this website