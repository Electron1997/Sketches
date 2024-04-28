CC = g++
CFLAGS = -I /home/mircopaul/Downloads/kl1p-0.4.2-sources/KL1p-0.4.2/include -L /home/mircopaul/Downloads/kl1p-0.4.2-sources/KL1p-0.4.2/bin/unix -lKLab64 -larmadillo

make:
	$(CC) -o main main.cpp */*.cpp Classes/*/*.cpp $(CFLAGS)

make prof:
	$(CC) -o main main.cpp */*.cpp Classes/*/*.cpp $(CFLAGS) -pg

make opt:
	$(CC) -o main main.cpp */*.cpp Classes/*/*.cpp $(CFLAGS) -O3 -pg