CXX = clang++
CXXFLAGS  = -m32 --std=c++11 -Os -Wall -pedantic -Wextra -Wno-unknown-pragmas -fomit-frame-pointer 
CXXFLAGS += -ffunction-sections -fdata-sections -Wl,-s -Wl,--gc-sections -Wl,--hash-style=sysv -fno-exceptions 
CXXFLAGS += -DNDEBUG 
CXXFLAGS += -DBOOST_EXCEPTION_DISABLE -DBOOST_NO_EXCEPTIONS

LDFLAGS = -m32

TARGET = Sample
SRCS = main.cpp DetectDebugger.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET) stripit

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

stripit:
	strip -S --strip-unneeded --remove-section=.note.gnu.gold-version \
		--remove-section=.comment --remove-section=.note \
		--remove-section=.note.gnu.build-id \
		--remove-section=.note.* \
		--remove-section=.note.ABI-tag $(TARGET)
	../../ELFkickers/sstrip/sstrip -z $(TARGET)

.PHONY: clean all stripit

clean:
	rm *.o $(TARGET)
