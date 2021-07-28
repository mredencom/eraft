#ifndef ERAFT_KV_SERVER_IMPL_H_
#define ERAFT_KV_SERVER_IMPL_H_

#include <iostream>

#include <eraftio/tinykvpb.grpc.pb.h>
#include <eraftio/raft_serverpb.pb.h>
#include <eraftio/metapb.pb.h>
#include <grpcpp/grpcpp.h>
#include <Kv/storage.h>
#include <Kv/raft_server.h>

using tinykvpb::TinyKv;
using grpc::Status;
using grpc::ServerContext;
using raft_serverpb::Done;

namespace kvserver
{

const std::string DEFAULT_ADDR = "127.0.0.1:12306";

class Server : public TinyKv::Service
{

public:

    Server();

    Server(std::string addr, RaftStorage* st);

    bool RunLogic();

    ~Server();

    Status Raft(ServerContext* context, const raft_serverpb::RaftMessage* request, Done* response) override;

    Status RawGet(ServerContext* context, const kvrpcpb::RawGetRequest* request, kvrpcpb::RawGetResponse* response) override;
   
    Status RawPut(ServerContext* context, const kvrpcpb::RawPutRequest* request, kvrpcpb::RawPutResponse* response) override;
    
    Status RawDelete(ServerContext* context, const kvrpcpb::RawDeleteRequest* request, kvrpcpb::RawDeleteResponse* response) override;
    
    Status RawScan(ServerContext* context, const kvrpcpb::RawScanRequest* request, kvrpcpb::RawScanResponse* response) override;

    Status Snapshot(ServerContext* context, const raft_serverpb::SnapshotChunk* request, Done* response) override;


private:

    std::string serverAddress_;

    RaftStorage* st_;

};

    
} // namespace kvserver

#endif