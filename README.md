# eraft
基于 C++ 实现的 Raft, Etcd Raft 的 c++ 实现版本 (Raft library implemented by C++, inspired by etcd golang version)

#### Overview

Raft is a protocol with which a cluster of nodes can maintain a replicated state machine. The state machine is kept in sync through the use of a replicated log. For more details on Raft, see "In Search of an Understandable Consensus Algorithm" (https://raft.github.io/raft.pdf) by Diego Ongaro and John Ousterhout.

#### Basic Dev Schedule

| Feature                       | Development Progress | Review |
| ----------------------------- | -------------------- | ------ |
| Leader election               |          done            |        |
| Log replication               |          done            |        |
| Log compaction                |          done            |        |
| Membership changes            |          done            |        |
| Leadership transfer extension |          done            |        |

#### Advance Dev Schedule

| Feature                                                      | Development Progress | Review |
| ------------------------------------------------------------ | -------------------- | ------ |
| Optimistic pipelining to reduce log replication latency      |                      |        |
| Flow control for log replication                             |                      |        |
| Batching Raft messages to reduce synchronized network I/O calls |                      |        |
| Batching log entries to reduce disk synchronized I/O         |                      |        |
| Writing to leader's disk in parallel                         |                      |        |
| Internal proposal redirection from followers to leader       |                      |        |
| Automatic stepping down when the leader loses quorum         |                      |        |
| Protection against unbounded log growth when quorum is lost  |                      |        |

#### Documents
See the (github wiki)[https://github.com/eraft-io/eraft/wiki] for more detail.

#### Code Style
https://google.github.io/styleguide/cppguide.html

#### Join Us on GoogleGroup

https://groups.google.com/g/eraftio

