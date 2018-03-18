CC = g++
TARGET = main
INCLUDE_DIRS+=-I/home/sensetime/libs/include
LD_LIBRARIE_DIRS+=-L/home/sensetime/libs/lib

INCLUDE_DIRS+=-I/home/liuliang/opencv3.2/include
LD_LIBRARIE_DIRS+=-L/home/liuliang/opencv3.2/lib

INCLUDE_DIRS+=-I/home/liuliang/Desktop/IBlending/include
LD_LIBRARIE_DIRS+=-L/home/liuliang/Desktop/IBlending/build

SRCS:=$(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
DLIBS+=/home/liuliang/Desktop/IBlending/build/api.o
DLIBS+=/home/liuliang/Desktop/IBlending/build/tools.o
DLIBS+=/home/liuliang/Desktop/IBlending/build/poisson_fr.o
DLIBS+=/home/liuliang/Desktop/IBlending/build/poisson_rect.o
DLIBS+=/home/liuliang/Desktop/IBlending/build/poisson_poly.o
DLIBS+=/home/liuliang/Desktop/IBlending/build/solve_equation.o
DLIBS+=/home/liuliang/Desktop/IBlending/build/drag_drop.o
DLIBS += -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_photo -lopencv_imgcodecs -lopencv_videoio -lopencv_shape

$(TARGET):$(OBJS)
	$(CC) $(LD_LIBRARIE_DIRS) -o $@ $^ $(DLIBS)  
clean:
	rm -rf $(TARGET) $(OBJS)
%.o:%.cpp
	$(CC) $(INCLUDE_DIRS) -o $@ -c $<
