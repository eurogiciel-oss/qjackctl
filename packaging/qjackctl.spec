Name:           qjackctl
Version:        0.3.11
Release:        0
Summary:        Graphical User Interface to Control JACK Servers
License:        GPL-2.0+
Group:          Multimedia/Audio
Url:            http://qjackctl.sf.net
Source:		http://downloads.sourceforge.net/%{name}/%{name}-%{version}.tar.gz
BuildRequires:  pkgconfig(alsa)
BuildRequires:  pkgconfig(jack)
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:	pkgconfig(Qt5Gui)
BuildRequires:	pkgconfig(Qt5Xml)
BuildRequires:	pkgconfig(Qt5DBus)
BuildRequires:	qt5-qttools-linguist
BuildRequires:  update-desktop-files
Requires:       jack
Requires:	qt5-qtwayland

%description
JACK Audio Connection Kit - Qt GUI Interface: A simple Qt application
to control the JACK server. Written in C++ around the Qt4 toolkit
for X11, most exclusively using Qt Designer. Provides a simple GUI
dialog for setting several JACK server parameters, which are properly
saved between sessions, and a way control of the status of the audio
server. With time, this primordial interface has become richer by
including a enhanced patchbay and connection control features.

%lang_package

%prep
%setup -q

%build
%reconfigure --disable-qt4 \
             --enable-qt5 \
             --disable-portaudio

%__make %{?_smp_mflags}

%install
%make_install

L="$PWD/%{name}.lang"; echo -n >"$L"
B="%{_datadir}/locale"
pushd "%{buildroot}${B}"
/bin/ls *.qm | while read qm; do
    l="${qm##*_}"
    l="${l%.qm}"
    echo "%lang($l) ${B}/${qm}" >>"$L"
done
popd


%files
%defattr(-,root,root)
%doc AUTHORS ChangeLog README TODO
%license COPYING
%{_bindir}/%{name}
%{_datadir}/applications/%{name}.desktop
%{_datadir}/icons/*/*/apps/%{name}.*
%doc %{_mandir}/man1/qjackctl.1*
