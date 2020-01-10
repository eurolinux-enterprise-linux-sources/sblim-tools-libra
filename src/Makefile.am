# ==================================================================
# (C) Copyright IBM Corp. 2005
#
# THIS FILE IS PROVIDED UNDER THE TERMS OF THE ECLIPSE PUBLIC LICENSE
# ("AGREEMENT"). ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS FILE
# CONSTITUTES RECIPIENTS ACCEPTANCE OF THE AGREEMENT.
#
# You can obtain a current copy of the Eclipse Public License from
# http://www.opensource.org/licenses/eclipse-1.0.php
#
# Author:       Wolfgang Taphorn <taphorn@de.ibm.com>
# Description:  Automake input file for Lib RA tools
# ==================================================================

# SBLIM Include Directory
sblimincdir = $(includedir)/sblim

# Start from an empty extra distribution file list
EXTRA_DIST=

# docdir defines where the documentation goes
docdir=$(datadir)/doc/$(PACKAGE)-$(VERSION)

#
# Automake instructions for documentation
#
doc_DATA=README AUTHORS COPYING 

# ADD EXTRA DOC FILES IF PRESENT
#doc_DATA+=
#EXTRA_DIST+=

#
# Automake instructions for 'src' dir
#
AM_CFLAGS = -Wall
AM_CPPFLAGS = -D_GNU_SOURCE

#  LibRaTools libraries
lib_LTLIBRARIES = libRaTools.la 

# LibRaTools sources
libRaTools_la_SOURCES = \
		src/smt_libra_conf.c \
		src/smt_libra_execscripts.c \
		src/smt_libra_monitors.c \
		src/smt_libra_rastr.c

# Installable Header Files
sbliminc_HEADERS = \
		src/smt_libra_conf.h \
		src/smt_libra_execscripts.h \
		src/smt_libra_monitors.h \
		src/smt_libra_rastr.h

# We must explicity add the RPM spec file to the distribution package
EXTRA_DIST+=$(PACKAGE).spec

