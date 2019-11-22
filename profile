# /etc/profile: system-wide .profile file for the Bourne shell (sh(1))
# and Bourne compatible shells (bash(1), ksh(1), ash(1), ...).

PATH="/usr/local/bin:/usr/bin:/bin"
EDITOR="vi"			# needed for packages like cron, git-commit
test -z "$TERM" && TERM="vt100"	# Basic terminal capab. For screen etc.

if [ ! -e /etc/localtime -a ! -e /etc/TZ ]; then
	TZ="UTC"		# Time Zone. Look at http://theory.uwinnipeg.ca/gnu/glibc/libc_303.html
				# for an explanation of how to set this to your local timezone.
	export TZ
fi

if [ "$HOME" = "/home/root" ]; then
   PATH=$PATH:/usr/local/sbin:/usr/sbin:/sbin
fi
if [ "$PS1" ]; then
# works for bash and ash (no other shells known to be in use here)
   PS1='\u@\h:\w\$ '
fi

if [ -d /etc/profile.d ]; then
  for i in /etc/profile.d/*.sh ; do
    if [ -f $i -a -r $i ]; then
      . $i
    fi
  done
  unset i
fi

export QT_QPA_PLATFORM=eglfs
export QT_QPA_DEBUG="1"
export QT_QPA_EGLFS_FB="/dev/fb0"
export QT_QPA_EGLFS_WIDTH=1024
export QT_QPA_EGLFS_HEIGHT=768
export QT_QPA_EGLFS_DEPTH=32
export QT_QPA_FONTDIR=/usr/lib/fonts

export PATH PS1 OPIEDIR QPEDIR QTDIR EDITOR TERM

umask 022

ulimit -c unlimited

# Platinum
# Gold
export MACHINE_TYPE=Platinum
#Alpha1
#Alpha2
export ALPHA_TYPE=Alpha2
