%define  RELEASE 1
%define  rel     %{?CUSTOM_RELEASE} %{!?CUSTOM_RELEASE:%RELEASE}

%define lib_name zthread

Name: ZThread
Version: 2.2.7
Release: %rel

Summary: cross-platform c++ multi-threading framework
Copyright: LGPL
Group: Development/Libraries
Vendor: Eric D. Crahen <crahen@cs.buffalo.edu>
Packager: Bastiaan Bakker <bastiaan.bakker@lifeline.nl>
Url: http://zthread.sourceforge.net/

Source: ftp://download.sourceforge.net/pub/sourceforge/zthread/%name-%version.tar.gz

Prefix: %_prefix
BuildRoot: %_tmppath/%name-%version-root

%description
ZThreads is an advanced platform-independant, Object-Oriented threading and
synchronization library. It has been designed and tested under POSIX & Win32
systems. It is not just another thread wrapper. 

%package devel
Summary: Development tools for ZThread
Group: Development/Libraries
Requires: %name = %version

%description devel
The %name-devel package contains the static libraries and header files
needed for development with %name.

%package doc
Summary: HTML formatted API documention for ZThread
Group: Development/Libraries
Requires: %name = %version

%description doc
The %name-doc package contains HTML formatted API documention generated by
the popular doxygen documentation generation tool.

%prep
rm -rf $RPM_BUILD_ROOT

%setup
CFLAGS="$RPM_OPT_FLAGS" ./configure --prefix=%{prefix} 

%build
make

%install
rm -rf $RPM_BUILD_ROOT

make prefix=$RPM_BUILD_ROOT%{prefix} install

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root,755)
%attr(755,root,root) %prefix/lib/lib*.so.*
%doc AUTHORS COPYING INSTALL NEWS README THANK.YOU LGPL.TXT TODO ChangeLog

%files devel
%defattr(-,root,root,755)
%prefix/include/*
%attr(755,root,root) %prefix/lib/lib*.so
%attr(644,root,root) %prefix/lib/*.*a

%files doc
%doc doc/html/*