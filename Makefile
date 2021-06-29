deps:
	@if [ ! -d "googletest" ]; then echo "googletest not present. Fetching googletest from internet..."; wget https://github.com/google/googletest/archive/release-1.10.0.tar.gz; tar xzvf release-1.10.0.tar.gz; rm -f release-1.10.0.tar.gz; mv googletest-release-1.10.0 googletest; fi
	@if [ ! -d "leveldb" ]; then echo "leveldb not present. Fetching leveldb-1.22 from internet..."; curl -s -L -O https://github.com/google/leveldb/archive/refs/tags/1.22.tar.gz; tar xzvf 1.22.tar.gz; rm -f 1.22.tar.gz; mv leveldb-1.22 leveldb; fi
