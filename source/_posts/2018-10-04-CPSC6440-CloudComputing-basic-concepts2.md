---
title: Cloud computing Basic concepts
date: 2018-10-04 15:09:31
updated: 2018-09-23 15:09:31
categories: Cloud computing
tags: Cloud computing
top:
---

Exam_2 Review Questions. Approximately 60% of the exam will be derived from these questions.

1. True or `False`: Users should store dynamic web content in S3.

2. What advantage is there in storing static web content in S3?
S3 is reliable, and durable. S3 is simple to ensure static web content is quickly accessible, always available, and secure.

3. Name four AWS constructs that allow you to control your VPC traffic.
Internet gateway, route tables, security group, network access control lists.

4. True or `False`: Security groups are stateless and Network ACLs are stateful. Explain what this means.
Security group: Return traffic is automatically allowed, regardless of any rules.
ACLs: Return traffic must be explicitly allowed by rules.

5. What is the purpose of an Internet Gateway? Is this a managed AWS service?
Yes, it’s a managed AWS service. An Internet gateway serves two purposes: to provide a target in your VPC route tables for Internet-routable traffic, and to perform network address translation (NAT) for instances that have been assigned public IPv4 addresses.

6. Describe the main difference between a public and a private subnet.
The main difference is the route for 0.0.0.0/0 in the associated route table. `A private subnet sets that route to a NAT instance.` Private subnet instances only need a private IP and internet traffic is routed through the NAT in the public subnet. You could also have no route to 0.0.0.0/0 to make it a truly private subnet with no internet access in or out. A public subnet routes 0.0.0.0/0 through an Internet Gateway (igw). Instances in a public subnet require public IPs to talk to the internet.

7. Expand each of the following acronyms of the following in the context of this class and provide a short description of what each is:

    - RTO  Recovery Time Objective, how quickly the system can recover?
    - RPO  Recovery Point Objective, how much data can you afford to lose?
    - **HA High Availability**
    - DNS Domain Name System
    - JSON JavaScript Object Notation
    - SOA Service Oriented Architecturegh 

> What is the difference about On-Premises HA Vs HA on AWS
> - On-Promises HA: 1. very expensive; 2. It's suitable only for mission-critical(派遣确定的) applications.
> - HA on AWS: 1.Multiple services. 2.Isolated redundancy data centers within each availability zone. 3.multiple availability zones within each region. 4. Region across the global. 5.Fault-tolerance service.

> From 100-CCA-31-EN-U3SG.pdf Module 3. 
8. **List the three main factors associated with High Availability.**
    - Fault tolerance: the **built-in redundancy** of an application’s component(组件).
    - Recoverability: the process, policies, and procedures related to **restoring service** after a catastrophic(灾难性的) event.
    - Scalability: the ability of application to **accommodate growth** without changing design.

9. What does enabling connection draining on an ELB do? Why is this important?
This enables the load balancer to complete in-flight requests made to instances that are de-registering or unhealthy. To ensure that a Classic Load Balancer stops sending requests to instances that are de-registering or unhealthy, while keeping the existing connections open.

10. `True` or False: Amazon CloudWatch allows the user to create custom metrics for their specific application.

11. What are three types of capacity parameters that an Auto Scaling Group defines?
Desired, minimum,maximum


12. Define a sample Auto Scale Policy.
The scaling policies that you define adjust the number of instances, within your minimum and maximum number of instances, based on the criteria that you specify.


1. True or `False`: When using Auto Scaling, you should be more cautious scaling in and try to avoid aggressive instance termination.

2. What are three languages AWS Lambda currently supports?
Python, JavaScript, java, c#

1. What AWS Service can be classified as Infrastructure as Code?
AWS CloudFormation

1. Define AWS CloudFormation.
AWS CloudFormation is a service that can be classified as infrastructure as code.

1. List seven possible sections that can be included in a AWS CloudFormation Template.
Description, metadata, parameters, mappings, conditions, transform, resources.

1. `True` or False: The more loosely your system is coupled the more easily it scales.

2. Define Services in the context of a SOA.
Services are self-contained units of functionality.

1. Define a Microservice and give an example.
Microservice: Small, independent processes within an SOA. Each process is focused on doing one small task. Processes communicate to each other using language-agnostic APIs.
~~**Example**: SNS? Use application load balancer with EC2 container service and auto scaling to implement mircoservice application.~~

1. What AWS Service provides a fully managed message queueing service?
SQS: Amazon Simple Queue Service is a fully managed message queueing service. Transmit any volume of messages at any level of throughput without losing messages or requiring other services to be always available.

1. What is a dead letter queue?
A dead letter queue is a queue of messages that could not be processed.

1. List three Amazon SQS use cases.
    - Work Queues: Decouple components of a distributed application that may not all process the same amount of work simultaneously.
    - Buffering Batch Operations: Add scalability and reliability to your architecture and smooth out temporary volume spikes without losing messages or increasing latency.
    - Request Offloading: Move slow operations off of interactive request paths by enqueueing the request.
    - Fan-out: Combine Amazon SQS with Amazon SNS to send identical copies of a message to multiple queues in parallel for simultaneous processing.
    - Auto Scaling: Use Amazon SQS queues to help determine the load on an application, and when combined with Auto Scaling, you can scale the number of Amazon EC2 instances out or in, depending on the volume of traffic.

1. List three subscriber types allowed by Amazon SNS.
    - Email(plain or JSON)
    - HTTP/HTTPS
    - Short Message Service(SMS) clients(USA only)
    - Amazon SQS queues
    - Mobile push messaging
    - AWS lambda function

1. List the characteristics of Amazon SNS.
Single published message, Order is not guaranteed, No recall, HTTP/HTTPS retry, 256 KB max per message

1. True or False: Amazon Kinesis is a database solution.
False? Amazon Kinesis makes it easy to collect, process, and analyze real-time, streaming data so you can get timely insights and react quickly to new information.

1. Amazon S3 provides _read-after-write_ consistency for PUTS of new objects and provides _eventual_ consistency for overwrites of PUTS and DELETES.


2. Define eventual consistency. Define read-after-write consistency. (no specific definition)
Eventual consistency is a consistency model used in distributed computing to achieve high availability that informally guarantees that, if no new updates are made to a given data item, eventually all accesses to that item will return the last updated value.
**Read-after-write consistency** is similar to a strongly consistent read returns a result that reflects all writes that received a successful response prior to the read.

30. Fill in the chart below:

| Null               | Amazon SNS          | Amazon SQS    |
| :----------------- | :------------------ | :------------ |
| Manage Persistence | No                  | Yes           |
| Delivery Mechanism | Push(Passive)       | Poll(Active)  |
| Producer/Consumer  | Publish(subscriber) | Send(receive) |

31. AWS Lambda starts code within `milliseconds` of an event.

2. List four triggers currently supported by AWS Lambda.
    - Amazon DynamoDB
    - S3
    - SNS
    - CloudWatch

3. How many different levels of resource allocation does AWS Lambda provide? What is the range of memory provided? What is the maximum runtime of a AWS Lambda function?
    - 23 different levels
    - 128M-1.5G
    - 5 minutes

4. True or `False`: Amazon CloudFront is located within AWS Edge Locations.


5. List three ways to expire contents within Amazon CloudFront.
    - Time to live (TTL)
    - Change Object Name
    - Invalidate Object

6. List the four pillars of the AWS Well-Architected Framework.
    - Security pillar
    - Reliability pillar
    - Performance pillar
    - Cost pillar

7. Describe three principles of the Security pillar.
    - Apply security at all layer: instead of just running security appliances at edge of your infrastructure, use firewalls and other security control on all of your resources.
    - Enable traceability: Log and audit all action and changes to your environment and access to yourservice
    - Automate response for security events: monitor and automatically trigger response to event-driven or condition driven alters

1. Describe three principles of the Reliability pillar.
    - Test recovery procedures: in cloud, you can test how your system fail, and you can validate your recovery procedures.
    - Automatically recover from failure: by monitoring a system for key performance indicators(KPIs), you can trigger automation when a threshold is breached.
    - Scaling horizontally to increase aggregate system reliability: replace one large sources with multiple small sources to reduce the impact of single failure on the overall system.  

2. Describe three principles of the Performance pillar.
    - Use advanced technologies: such as edge location or edge service, can reduce latency for service and load on your system.
    - Use “serverless” Architecture: serverless architectures remove the need for you to run and maintain servers to carry out traditional compute activities. 
    - Go global in minutes: easily deploy your system in multiple regions around the world with just few clicks.

3. Describe three principles of the Cost pillar.
![](/images/in-post/2018-10-04-CPSC6440-CloudComputing-basic-concepts2/2018-10-03-22-28-10.png)


4.  Test recovery procedures: in cloud, you can test how your system fail, and you can validate your recovery procedures.

5.  Automatically recover from failure: by monitoring a system for key performance indicators(KPIs), you can trigger automation when a threshold is breached.

6.  Scaling horizontally to increase aggregate system reliability: replace one large sources with multiple small sources to reduce the impact of single failure on the overall system.

7.   Describe three principles of the Performance pillar.

8.  Use advanced technologies: such as edge location or edge service, can reduce latency for service and load on your system.
    
9.  Use “serverless” Architecture: serverless architectures remove the need for you to run and maintain servers to carry out traditional compute activities.
    
10. Go global in minutes: easily deploy your system in multiple regions around the world with just few clicks.

11. What are three things might you troubleshoot if your instance times out?
    - check your routes
    - check your security group rules
    - check your network ACLs

  

12. What are three things might you troubleshoot if your network is unreachable?
    - Check your routes
    - Check your security group rules
    - Check your Network ACLs

13. What are three things might you troubleshoot if the CPU load on your database is too high?
    - Optimize your queries
    - Use read replicas
    - Ensure your are using the best instance type

14. What are three things might you troubleshoot if your access is denied?
    - Verify you have permission to call that action on that resource
    - verify that any resource policies specify you as a principal and grant you access

15. Describe five tradeoffs, in a table, of Instance Store, EBS, S3, and Glacier.
![https://lh5.googleusercontent.com/fJF5VSlHpe8MKd-ITv9MrUVVwi8WhTGd03AfhURy1DQzoaWUzx_VCxpgqcfz-O9SEnWg2nO3_MaUblXGxFIFgx6B5LViU8g8s3oEis9cVu5xMC9_EwjRA42ejU_9omoSCXY5gVfK](https://lh6.googleusercontent.com/KKHztJzarMZvNVHJc63FIOplldn-oabFumiYNYsjbG7G17_KeVmjMX14y_EQ0D9K0HRBjvHT4KkEpwhrpEGQ1g3hD4fvJShriR7E2EXrq6WVLhUwVZ8IrMfzqt3rrzNIx_J7KD_qD39vAn-qDw)

1. Describe five tradeoffs, in a table, of DynamoDB, RDS, and Redshift.
![https://lh5.googleusercontent.com/pkfPXpoE8Bk1yVHNrrjT0EyGIebfm3J_KQFkCie2GSLtUHUaS57Ype1OGuFb_Q3xHa5fofDgkcjgeIDbGi0YGQ1hZNtzM5o58_TgFXY6GwE3mZPmUz57wVZC1v5m5pGnicWjWzJt](https://lh5.googleusercontent.com/rFTk0O3qw9MpIvQAmOPaS5tumdlTSIbXFHAXQOpcOJkpj3UEnmaii-ohG3oqhhI2rNPsFQZPzd8aVw8JYAgM6vWW5VB3Ne3pEAzKra9PSrQ2DzB-rKdyAPYQ4q1TNrMyjkIKL9FFDR5KfvBcNw)

1. List five EC2 Purchasing Options
    - On-demand instances
    - Spot instances
    - Reserved instances
    - Dedicated instances
    - Dedicated hosts

2. Spot instances are provided a termination notice `24 times?` prior to termination (i.e., how much time?)

3. List and describe the differences of three different payment models for EC2 Reserved Instances.
    - All upfront: pay for the entire Reserved Instance with one upfront payment.
    - Partial Upfront: make a low upfront payment, and then you are charged a discounted hourly rate for the instance for the duration of the Reserved Instance term
    - No Upfront: Does not require any upfront payments and provides a discounted hourly rate for the duration of the term.


4.  All upfront: pay for the entire Reserved Instance with one upfront payment.
    
5.  Partial Upfront: make a low upfront payment, and then you are charged a discounted hourly rate for the instance for the duration of the Reserved Instance term
    
6.  No Upfront: Does not require any upfront payments and provides a discounted hourly rate for the duration of the term.
    

  

7.  Describe the difference between a Dedicated Instance and a Dedicated Host.
    - Dedicated Instances - You pay for the instances, but they get placed on whatever dedicated hardware Amazon decides.
    - Dedicated Host - You pay for the entire physical server and can, in effect, run instances on it as you please.
    - A Dedicated Host and a dedicated instance is that a Dedicated Host gives you additional visibility and control over how instances are placed on a physical server, and you can consistently deploy your instances to the same physical server over time. As a result, Dedicated Hosts enable you to use your existing server-bound software licenses and address corporate compliance and regulatory requirements.

8.  Describe one advantage of each of the following High Availability Patterns (may not get to this one)
    - Job Observer
    - Scheduled Scale-Out
    - Multi-AZ
    - High Availability Database
    - Floating IP
    - Floating Interface
    - State Sharing