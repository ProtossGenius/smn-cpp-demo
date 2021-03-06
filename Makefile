##Tail
build: prebuild
	cd build && make -j8

debug:

qrun: build
	sudo ./build/smn-rip-demo
test:

install: 

update_cmake: prebuild
	rm ./build/* -rf
	cd build && cmake ..

clean:
	rm -rf ./pb rm ./cpp ./smn_itf
	cd ./ric_code/ && rm *.cc *.h *.cpp -f
	cd ./ric_code/pb && rm *.cc *.h *.cpp -f

prebuild: clean
	smnrpc-autocode -cfg ./datas/cfgs/testrpc.json	
