Lecture 12
---

# Basics of Networking

## Lecture

Slides ([PDF](OS_Lecture_12.pdf), [PPTX](OS_Lecture_12.pptx)).

<!---
Outline:
-->

## Workshop

<!---
* [Part 1](workshop1.md).
* [Part 2](workshop2.md).
-->

Viewing standard ports for various services:
```bash
cat /etc/services | grep http
# Updated from https://www.iana.org/assignments/service-names-port-numbers/service-names-port-numbers.xhtml .
http		80/tcp		www		# WorldWideWeb HTTP
https		443/tcp				# http protocol over TLS/SSL
https		443/udp				# HTTP/3
http-alt	8080/tcp	webcache	# WWW caching service
```

Viewing/editing the [/etc/hosts](https://en.wikipedia.org/wiki/Hosts_%28file%29) file: 
```bash
cat /etc/hosts
127.0.0.1	localhost
127.0.1.1	huawei-ThinkPad-T490s
158.160.144.239	ejudge

# The following lines are desirable for IPv6 capable hosts
::1     ip6-localhost ip6-loopback
fe00::0 ip6-localnet
ff00::0 ip6-mcastprefix
ff02::1 ip6-allnodes
ff02::2 ip6-allrouters
```

Querying DNS with [nslookup](https://en.wikipedia.org/wiki/Nslookup):
```bash
nslookup hse.ru
Server:		127.0.0.53
Address:	127.0.0.53#53

Non-authoritative answer:
Name:	hse.ru
Address: 178.248.234.104
```

## Homework

__TODO__

## References

* Network Programming. Chapter 11 in [[CSPP]](../../books.md)
* Sockets: Fundamentals Of TCP/IP Networks. Chapter 58 in [[TLPI]](../../books.md)
* [TCP/IP](https://en.wikipedia.org/wiki/Internet_protocol_suite) (Wikipedia)
* [DNS](https://en.wikipedia.org/wiki/Domain_Name_System) (Wikipedia)
 