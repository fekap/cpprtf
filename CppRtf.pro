TEMPLATE = subdirs
#Lets build projects in order of it's enumeration in SUBDIRS variable
CONFIG += ordered
SUBDIRS += \
	boost\
        cpprtf-lib \
        samples
