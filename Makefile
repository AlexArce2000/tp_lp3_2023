Cap1 := src/Cap1
Listing1.1 := $(Cap1) 
Listing1.2 := $(Cap1) 
Listing1.3 := $(Cap1)
Listing2.1 := src/Cap2/Listing2.1
Listing2.2 := src/Cap2/Listing2.2
Listing2.3 := src/Cap2/Listing2.3
Listing2.4 := src/Cap2/Listing2.4
Listing2.5 := src/Cap2/Listing2.5
Listing2.6 := src/Cap2/Listing2.6
Listing2.7 := src/Cap2/Listing2.7
Listing2.8 := src/Cap2/Listing2.8
Listing2.9 := src/Cap2/Listing2.9
Listing3.1 := src/Cap3/Listing3.1
Listing3.2 := src/Cap3/Listing3.2
Listing3.3 := src/Cap3/Listing3.3
Listing3.4 := src/Cap3/Listing3.4
Listing3.5 := src/Cap3/Listing3.5
Listing3.6 := src/Cap3/Listing3.6
Listing3.7 := src/Cap3/Listing3.7
Listing4.1 := src/Cap4/Listing4.1
Listing4.2 := src/Cap4/Listing4.2
Listing4.3 := src/Cap4/Listing4.3
Listing4.4 := src/Cap4/Listing4.4
Listing4.5 := src/Cap4/Listing4.5
Listing4.6 := src/Cap4/Listing4.6
Listing4.7 := src/Cap4/Listing4.7
Listing4.8 := src/Cap4/Listing4.8
Listing4.9 := src/Cap4/Listing4.9
Listing4.10 := src/Cap4/Listing4.10
Listing4.11 := src/Cap4/Listing4.11
Listing4.12 := src/Cap4/Listing4.12
Listing4.13 := src/Cap4/Listing4.13
Listing4.14 := src/Cap4/Listing4.14
Listing4.15 := src/Cap4/Listing4.15

listings := \
	$(Cap1) \
	$(Listing2.1) \
	$(Listing2.2) \
	$(Listing2.3) \
	$(Listing2.4) \
	$(Listing2.5) \
	$(Listing2.6) \
	$(Listing2.7) \
	$(Listing2.8) \
	$(Listing2.9) \
	$(Listing3.1) \
	$(Listing3.2) \
	$(Listing3.3) \
	$(Listing3.4) \
	$(Listing3.5) \
	$(Listing3.6) \
	$(Listing3.7) \
	$(Listing4.1) \
	$(Listing4.2) \
	$(Listing4.3) \
	$(Listing4.4) \
	$(Listing4.5) \
	$(Listing4.6) \
	$(Listing4.7) \
	$(Listing4.8) \
	$(Listing4.9) \
	$(Listing4.10) \
	$(Listing4.11) \
	$(Listing4.12) \
	$(Listing4.13) \
	$(Listing4.14) \
	$(Listing4.15)

.PHONY: all clean $(listings)
all: $(listings)
$(listings):
	$(MAKE) --directory=$@
%:
	$(if $($@), $(MAKE) --directory=$($@), $(error comando o Listing "$@" no existe))

clean:
	rm -rf build