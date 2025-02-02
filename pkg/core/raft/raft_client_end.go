// Copyright [2022] [WellWood] [wellwood-x@googlegroups.com]

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

// 	http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

package raft

import (
	log "github.com/eraft-io/eraft/pkg/log"

	pb "github.com/eraft-io/eraft/pkg/protocol"
	"google.golang.org/grpc"
)

type RaftClientEnd struct {
	id             uint64
	addr           string
	conns          []*grpc.ClientConn
	raftServiceCli *pb.RaftServiceClient
}

func (raftcli *RaftClientEnd) Id() uint64 {
	return raftcli.id
}

func (raftcli *RaftClientEnd) GetRaftServiceCli() *pb.RaftServiceClient {
	return raftcli.raftServiceCli
}

func MakeRaftClientEnd(addr string, id uint64) *RaftClientEnd {
	conn, err := grpc.Dial(addr, grpc.WithInsecure())
	if err != nil {
		log.MainLogger.Error().Msgf("faild to connect: %v", err)
	}
	conns := []*grpc.ClientConn{}
	conns = append(conns, conn)
	rpcClient := pb.NewRaftServiceClient(conn)
	return &RaftClientEnd{
		id:             id,
		addr:           addr,
		conns:          conns,
		raftServiceCli: &rpcClient,
	}
}

func (raftcli *RaftClientEnd) CloseAllConn() {
	for _, conn := range raftcli.conns {
		conn.Close()
	}
}
