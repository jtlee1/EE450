
CXX = g++


all: serverA.cpp serverB.cpp serverC.cpp serverM.cpp client.cpp monitor.cpp
	$(CXX) -std=c++11 -w -o serverA serverA.cpp
	$(CXX) -std=c++11 -w -o serverB serverB.cpp
	$(CXX) -std=c++11 -w -o serverC serverC.cpp
	$(CXX) -std=c++11 -w -o serverM serverM.cpp
	$(CXX) -std=c++11 -w -o monitor monitor.cpp
	$(CXX) -std=c++11 -w -o client client.cpp



clean:
	$(RM) serverA
	$(RM) serverB
	$(RM) serverC
	$(RM) serverM
	$(RM) client
	$(RM) monitor
