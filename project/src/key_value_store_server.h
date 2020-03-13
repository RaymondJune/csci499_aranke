#include <glog/logging.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

#include "key_value_store.grpc.pb.h"
#include "key_value_store.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;

using kvstore::GetReply;
using kvstore::GetRequest;
using kvstore::KeyValueStore;
using kvstore::PutReply;
using kvstore::PutRequest;
using kvstore::RemoveReply;
using kvstore::RemoveRequest;

class KeyValueStoreServer final : public KeyValueStore::Service {
 public:
  Status put(ServerContext* context, const PutRequest* request,
             PutReply* response) override;
  Status get(ServerContext* context,
             ServerReaderWriter<GetReply, GetRequest>* stream) override;
  Status remove(ServerContext* context, const RemoveRequest* request,
                RemoveReply* response) override;

 private:
  KvStore kv_store_;
};