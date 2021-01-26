package rpc_itf

import "net"

type Login interface {
	DoLogin(user, pswd string, code int) (status, err string)
	Test1(a []string, b []int, c []uint, d []uint64, e []int32) []int
	Test2(key string, c net.Conn) bool
}
