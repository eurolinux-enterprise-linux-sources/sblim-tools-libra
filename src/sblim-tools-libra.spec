#
#
# Package spec for sblim-tools-libra
#

BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}

Summary: SBLIM Common Resource Access Library for WBEM-SMT tasks
Name: sblim-tools-libra
Version: 1.0
Release: 1
Group: Systems Management/Libraries/Instrumentation
URL: http://www.sblim.org
License: EPL

Source0: http://prdownloads.sourceforge.net/sblim/%{name}-%{version}.tar.bz2

%Description
The tools-libra package provides common functionality required by 
the task-specific resource access layers of wbem-smt tasks such as 
cmpi-dns and cmpi-samba.


%Package devel
Summary: SBLIM Common Resource Access Library for WBEM-SMT tasks Header Development Files
Group: Systems Management/Libraries/Instrumentation
Requires: %{name} = %{version}

%Description devel
The tools-libra package provides common functionality required by 
the task-specific resource access layers of the wbem-smt tasks such as 
cmpi-dns and cmpi-samba.
This package includes the header files and link libraries for dependent 
provider packages

%prep

%setup -n %{name}-%{version}

export PATCH_GET=0

#%patch0 -p0

%build

%configure
make

%clean
if [ "x${RPM_BUILD_ROOT}" != "x" ] ; then
 rm -rf ${RPM_BUILD_ROOT}
fi

%install
if [ "x${RPM_BUILD_ROOT}" != "x" ] ; then
 rm -rf ${RPM_BUILD_ROOT}
fi

make DESTDIR=$RPM_BUILD_ROOT install

# remove unused libtool files
rm -f $RPM_BUILD_ROOT/%{_libdir}/*a
strip $RPM_BUILD_ROOT/%{_libdir}/*.so*


%pre

%post
/sbin/ldconfig

%preun

%postun 
/sbin/ldconfig

%files
%defattr(-,root,root) 
%docdir %{_datadir}/doc/%{name}-%{version}
%{_datadir}/doc/%{name}-%{version}
%{_libdir}/libRaTools.so.*

%files devel
%defattr(-,root,root)
%dir %{_includedir}/sblim
%{_includedir}/sblim/smt_libra*.h
%{_libdir}/libRaTools.so


%changelog
* Tue Sep 15 2009 Jeremy Bongio <jbongio@us.ibm.com> 1.0-1
  - Change licensing from CPL to EPL

* Wed Jun 17 2009 Jeremy Bongio <jbongio@us.ibm.com> 0.5.6-1
  - Maintenance release

* Mon May 12 2008 Sam Kannan <skanan@us.ibm.com> 0.5.5-1
  - Maintenance release
  
* Wed Apr 30 2008 Sam Kannan <skanan@us.ibm.com> 0.5.4-1
  - Maintenance release

* Tue Dec 11 2007 Sam Kannan <skanan@us.ibm.com> 0.5.3-1
  - 1845495  tools-libra: Include proper group definition for RPM build

* Fri Sep 14 2007 Wolfgang Taphorn <taphorn@de.ibm.com> 0.5.2-1
  - Increase of version number

* Mon Aug 27 2007 Wolfgang Taphorn <taphorn@de.ibm.com> 0.5.1-1
  - Increase of version number

* Tue Jul 31 2007 Wolfgang Taphorn <taphorn@de.ibm.com> 0.5.0-1
  - Inclusion of fixes for the following issues:
    o 1764884  tools-libra: More specific on package content

* Fri Dec 1 2006 Wolfgang Taphorn <taphorn@de.ibm.com> 0.2.3-1
  - Functional enhancements
  - Removed 'DEBUG' defines

* Wed Oct 11 2006 Wolfgang Taphorn <taphorn@de.ibm.com> 0.2.2-1
  - Cleanup work

* Sat Jul 22 2006 Wolfgang Taphorn <taphorn@de.ibm.com> 0.2.1-1
  - Stabelized code

* Wed Aug 25 2005 Wolfgang Taphorn <taphorn@de.ibm.com> 0.1.1-1
  - initial support
  
