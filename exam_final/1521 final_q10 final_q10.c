STAT(2)                    Linux Programmer's Manual                   STAT(2)



NNAAMMEE
       stat, fstat, lstat, fstatat - get file status

SSYYNNOOPPSSIISS
       ##iinncclluuddee <<ssyyss//ttyyppeess..hh>>
       ##iinncclluuddee <<ssyyss//ssttaatt..hh>>
       ##iinncclluuddee <<uunniissttdd..hh>>

       iinntt ssttaatt((ccoonnsstt cchhaarr **_p_a_t_h_n_a_m_e,, ssttrruucctt ssttaatt **_b_u_f));;
       iinntt ffssttaatt((iinntt _f_d,, ssttrruucctt ssttaatt **_b_u_f));;
       iinntt llssttaatt((ccoonnsstt cchhaarr **_p_a_t_h_n_a_m_e,, ssttrruucctt ssttaatt **_b_u_f));;

       ##iinncclluuddee <<ffccnnttll..hh>>           /* Definition of AT_* constants */
       ##iinncclluuddee <<ssyyss//ssttaatt..hh>>

       iinntt ffssttaattaatt((iinntt _d_i_r_f_d,, ccoonnsstt cchhaarr **_p_a_t_h_n_a_m_e,, ssttrruucctt ssttaatt **_b_u_f,,
                   iinntt _f_l_a_g_s));;

   Feature Test Macro Requirements for glibc (see ffeeaattuurree__tteesstt__mmaaccrrooss(7)):

       llssttaatt():
           /* glibc 2.19 and earlier */ _BSD_SOURCE
               || /* Since glibc 2.20 */ _DEFAULT_SOURCE
               || _XOPEN_SOURCE >= 500
               || /* Since glibc 2.10: */ _POSIX_C_SOURCE >= 200112L

       ffssttaattaatt():
           Since glibc 2.10:
               _POSIX_C_SOURCE >= 200809L
           Before glibc 2.10:
               _ATFILE_SOURCE

DDEESSCCRRIIPPTTIIOONN
       These  functions return information about a file, in the buffer pointed
       to by _b_u_f.  No permissions are required on the file itself, but—in  the
       case  of  ssttaatt(), ffssttaattaatt(), and llssttaatt()—execute (search) permission is
       required on all of the directories in _p_a_t_h_n_a_m_e that lead to the file.

       ssttaatt() and ffssttaattaatt() retrieve information about the file pointed to  by
       _p_a_t_h_n_a_m_e; the differences for ffssttaattaatt() are described below.

       llssttaatt()  is  identical to ssttaatt(), except that if _p_a_t_h_n_a_m_e is a symbolic
       link, then it returns information about the link itself, not  the  file
       that it refers to.

       ffssttaatt() is identical to ssttaatt(), except that the file about which infor‐
       mation is to be retrieved is specified by the file descriptor _f_d.

       All of these system calls return a _s_t_a_t structure, which  contains  the
       following fields:

           struct stat {
               dev_t     st_dev;         /* ID of device containing file */
               ino_t     st_ino;         /* inode number */
               mode_t    st_mode;        /* file type and mode */
               nlink_t   st_nlink;       /* number of hard links */
               uid_t     st_uid;         /* user ID of owner */
               gid_t     st_gid;         /* group ID of owner */
               dev_t     st_rdev;        /* device ID (if special file) */
               off_t     st_size;        /* total size, in bytes */
               blksize_t st_blksize;     /* blocksize for filesystem I/O */
               blkcnt_t  st_blocks;      /* number of 512B blocks allocated */

               /* Since Linux 2.6, the kernel supports nanosecond
                  precision for the following timestamp fields.
                  For the details before Linux 2.6, see NOTES. */

               struct timespec st_atim;  /* time of last access */
               struct timespec st_mtim;  /* time of last modification */
               struct timespec st_ctim;  /* time of last status change */

           #define st_atime st_atim.tv_sec      /* Backward compatibility */
           #define st_mtime st_mtim.tv_sec
           #define st_ctime st_ctim.tv_sec
           };

       _N_o_t_e_:  the order of fields in the _s_t_a_t structure varies somewhat across
       architectures.  In addition, the definition above  does  not  show  the
       padding bytes that may be present between some fields on various archi‐
       tectures.  Consult the glibc and kernel source code if you need to know
       the details.

       _N_o_t_e_:  For  performance and simplicity reasons, different fields in the
       _s_t_a_t structure may contain state  information  from  different  moments
       during  the  execution  of the system call.  For example, if _s_t___m_o_d_e or
       _s_t___u_i_d is changed by another process by calling cchhmmoodd(2)  or  cchhoowwnn(2),
       ssttaatt()  might  return  the old _s_t___m_o_d_e together with the new _s_t___u_i_d, or
       the old _s_t___u_i_d together with the new _s_t___m_o_d_e.

       The _s_t___d_e_v field describes the device on which this file resides.  (The
       mmaajjoorr(3)  and  mmiinnoorr(3) macros may be useful to decompose the device ID
       in this field.)

       The _s_t___r_d_e_v field describes the device that this  file  (inode)  repre‐
       sents.

       The  _s_t___s_i_z_e  field gives the size of the file (if it is a regular file
       or a symbolic link) in bytes.  The size  of  a  symbolic  link  is  the
       length of the pathname it contains, without a terminating null byte.

       The  _s_t___b_l_o_c_k_s  field  indicates  the number of blocks allocated to the
       file, 512-byte units.  (This may be smaller than _s_t___s_i_z_e/512  when  the
       file has holes.)

       The  _s_t___b_l_k_s_i_z_e  field  gives  the  "preferred" blocksize for efficient
       filesystem I/O.  (Writing to a file in  smaller  chunks  may  cause  an
       inefficient read-modify-rewrite.)

       Not  all  of  the  Linux  filesystems implement all of the time fields.
       Some filesystem types allow mounting in such a  way  that  file  and/or
       directory  accesses do not cause an update of the _s_t___a_t_i_m_e field.  (See
       _n_o_a_t_i_m_e, _n_o_d_i_r_a_t_i_m_e, and _r_e_l_a_t_i_m_e in mmoouunntt(8), and related  information
       in mmoouunntt(2).)  In addition, _s_t___a_t_i_m_e is not updated if a file is opened
       with the OO__NNOOAATTIIMMEE; see ooppeenn(2).

       The field _s_t___a_t_i_m_e  is  changed  by  file  accesses,  for  example,  by
       eexxeeccvvee(2),  mmkknnoodd(2), ppiippee(2), uuttiimmee(2), and rreeaadd(2) (of more than zero
       bytes).  Other routines, like mmmmaapp(2), may or may not update _s_t___a_t_i_m_e.

       The field _s_t___m_t_i_m_e is changed by file modifications,  for  example,  by
       mmkknnoodd(2),  ttrruunnccaattee(2),  uuttiimmee(2),  and  wwrriittee(2)  (of  more  than zero
       bytes).  Moreover, _s_t___m_t_i_m_e of a directory is changed by  the  creation
       or  deletion  of  files  in  that directory.  The _s_t___m_t_i_m_e field is _n_o_t
       changed for changes in owner, group, hard link count, or mode.

       The field _s_t___c_t_i_m_e is changed by writing or by setting  inode  informa‐
       tion (i.e., owner, group, link count, mode, etc.).

       POSIX  refers to the _s_t___m_o_d_e bits corresponding to the mask SS__IIFFMMTT (see
       below) as the _f_i_l_e _t_y_p_e, the 12 bits corresponding to the mask 07777 as
       the  _f_i_l_e _m_o_d_e _b_i_t_s and the least significant 9 bits (0777) as the _f_i_l_e
       _p_e_r_m_i_s_s_i_o_n _b_i_t_s.

       The following mask values are defined for the file type of the  _s_t___m_o_d_e
       field:

           SS__IIFFMMTT     0170000   bit mask for the file type bit field

           SS__IIFFSSOOCCKK   0140000   socket
           SS__IIFFLLNNKK    0120000   symbolic link
           SS__IIFFRREEGG    0100000   regular file
           SS__IIFFBBLLKK    0060000   block device
           SS__IIFFDDIIRR    0040000   directory
           SS__IIFFCCHHRR    0020000   character device
           SS__IIFFIIFFOO    0010000   FIFO

       Thus, to test for a regular file (for example), one could write:

           stat(pathname, &sb);
           if ((sb.st_mode & S_IFMT) == S_IFREG) {
               /* Handle regular file */
           }

       Because  tests  of  the  above  form  are common, additional macros are
       defined by POSIX to allow the test of the file type in  _s_t___m_o_d_e  to  be
       written more concisely:

           SS__IISSRREEGG(m)  is it a regular file?

           SS__IISSDDIIRR(m)  directory?

           SS__IISSCCHHRR(m)  character device?

           SS__IISSBBLLKK(m)  block device?

           SS__IISSFFIIFFOO(m) FIFO (named pipe)?

           SS__IISSLLNNKK(m)  symbolic link?  (Not in POSIX.1-1996.)

           SS__IISSSSOOCCKK(m) socket?  (Not in POSIX.1-1996.)

       The preceding code snippet could thus be rewritten as:

           stat(pathname, &sb);
           if (S_ISREG(sb.st_mode)) {
               /* Handle regular file */
           }

       The definitions of most of the above file type test macros are provided
       if any of the following feature test macros is defined: __BBSSDD__SSOOUURRCCEE (in
       glibc  2.19  and earlier), __SSVVIIDD__SSOOUURRCCEE (in glibc 2.19 and earlier), or
       __DDEEFFAAUULLTT__SSOOUURRCCEE (in glibc 2.20 and later).  In addition, definitions of
       all  of the above macros except SS__IIFFSSOOCCKK and SS__IISSSSOOCCKK() are provided if
       __XXOOPPEENN__SSOOUURRCCEE is defined.  The  definition  of  SS__IIFFSSOOCCKK  can  also  be
       exposed by defining __XXOOPPEENN__SSOOUURRCCEE with a value of 500 or greater.

       The definition of SS__IISSSSOOCCKK() is exposed if any of the following feature
       test macros is  defined:  __BBSSDD__SSOOUURRCCEE  (in  glibc  2.19  and  earlier),
       __DDEEFFAAUULLTT__SSOOUURRCCEE  (in  glibc 2.20 and later), __XXOOPPEENN__SSOOUURRCCEE with a value
       of 500 or greater, or  __PPOOSSIIXX__CC__SSOOUURRCCEE  with  a  value  of  200112L  or
       greater.

       The  following  mask  values are defined for the file mode component of
       the _s_t___m_o_d_e field:

           SS__IISSUUIIDD     04000   set-user-ID bit
           SS__IISSGGIIDD     02000   set-group-ID bit (see below)
           SS__IISSVVTTXX     01000   sticky bit (see below)

           SS__IIRRWWXXUU     00700   owner has read, write, and execute permission
           SS__IIRRUUSSRR     00400   owner has read permission
           SS__IIWWUUSSRR     00200   owner has write permission
           SS__IIXXUUSSRR     00100   owner has execute permission

           SS__IIRRWWXXGG     00070   group has read, write, and execute permission
           SS__IIRRGGRRPP     00040   group has read permission
           SS__IIWWGGRRPP     00020   group has write permission
           SS__IIXXGGRRPP     00010   group has execute permission

           SS__IIRRWWXXOO     00007   others (not in group) have read,  write,  and
                               execute permission
           SS__IIRROOTTHH     00004   others have read permission
           SS__IIWWOOTTHH     00002   others have write permission
           SS__IIXXOOTTHH     00001   others have execute permission

       The  set-group-ID bit (SS__IISSGGIIDD) has several special uses.  For a direc‐
       tory, it indicates that BSD semantics is to be used for that directory:
       files created there inherit their group ID from the directory, not from
       the effective group ID of the creating process, and directories created
       there will also get the SS__IISSGGIIDD bit set.  For a file that does not have
       the group execution bit (SS__IIXXGGRRPP) set, the set-group-ID  bit  indicates
       mandatory file/record locking.

       The  sticky  bit  (SS__IISSVVTTXX)  on  a  directory means that a file in that
       directory can be renamed or deleted only by the owner of the  file,  by
       the owner of the directory, and by a privileged process.

   ffssttaattaatt(())
       The  ffssttaattaatt()  system call operates in exactly the same way as ssttaatt(),
       except for the differences described here.

       If the pathname given in _p_a_t_h_n_a_m_e is relative, then it  is  interpreted
       relative  to  the  directory  referred  to by the file descriptor _d_i_r_f_d
       (rather than relative to the current working directory of  the  calling
       process, as is done by ssttaatt() for a relative pathname).

       If  _p_a_t_h_n_a_m_e  is relative and _d_i_r_f_d is the special value AATT__FFDDCCWWDD, then
       _p_a_t_h_n_a_m_e is interpreted relative to the current  working  directory  of
       the calling process (like ssttaatt()).

       If _p_a_t_h_n_a_m_e is absolute, then _d_i_r_f_d is ignored.

       _f_l_a_g_s  can  either  be 0, or include one or more of the following flags
       ORed:

       AATT__EEMMPPTTYY__PPAATTHH (since Linux 2.6.39)
              If _p_a_t_h_n_a_m_e is an empty string, operate on the file referred  to
              by  _d_i_r_f_d (which may have been obtained using the ooppeenn(2) OO__PPAATTHH
              flag).  If _d_i_r_f_d is AATT__FFDDCCWWDD, the call operates on  the  current
              working directory.  In this case, _d_i_r_f_d can refer to any type of
              file, not just a directory.  This flag is Linux-specific; define
              __GGNNUU__SSOOUURRCCEE to obtain its definition.

       AATT__NNOO__AAUUTTOOMMOOUUNNTT (since Linux 2.6.38)
              Don't  automount the terminal ("basename") component of _p_a_t_h_n_a_m_e
              if it is a directory that is an automount  point.   This  allows
              the  caller  to  gather attributes of an automount point (rather
              than the location it would mount).  This flag  can  be  used  in
              tools  that  scan  directories to prevent mass-automounting of a
              directory of automount points.  The AATT__NNOO__AAUUTTOOMMOOUUNNTT flag has  no
              effect  if  the mount point has already been mounted over.  This
              flag is Linux-specific; define __GGNNUU__SSOOUURRCCEE to obtain its defini‐
              tion.

       AATT__SSYYMMLLIINNKK__NNOOFFOOLLLLOOWW
              If  _p_a_t_h_n_a_m_e  is a symbolic link, do not dereference it: instead
              return information about the link  itself,  like  llssttaatt().   (By
              default, ffssttaattaatt() dereferences symbolic links, like ssttaatt().)

       See ooppeennaatt(2) for an explanation of the need for ffssttaattaatt().

RREETTUURRNN VVAALLUUEE
       On  success,  zero is returned.  On error, -1 is returned, and _e_r_r_n_o is
       set appropriately.

EERRRROORRSS
       EEAACCCCEESS Search permission is denied for one of the  directories  in  the
              path prefix of _p_a_t_h_n_a_m_e.  (See also ppaatthh__rreessoolluuttiioonn(7).)

       EEBBAADDFF  _f_d is not a valid open file descriptor.

       EEFFAAUULLTT Bad address.

       EELLOOOOPP  Too many symbolic links encountered while traversing the path.

       EENNAAMMEETTOOOOLLOONNGG
              _p_a_t_h_n_a_m_e is too long.

       EENNOOEENNTT A  component of _p_a_t_h_n_a_m_e does not exist, or _p_a_t_h_n_a_m_e is an empty
              string.

       EENNOOMMEEMM Out of memory (i.e., kernel memory).

       EENNOOTTDDIIRR
              A component of the path prefix of _p_a_t_h_n_a_m_e is not a directory.

       EEOOVVEERRFFLLOOWW
              _p_a_t_h_n_a_m_e or _f_d refers to a file whose  size,  inode  number,  or
              number  of  blocks  cannot  be represented in, respectively, the
              types _o_f_f___t, _i_n_o___t, or _b_l_k_c_n_t___t.  This error can occur when, for
              example,  an  application  compiled on a 32-bit platform without
              _-_D___F_I_L_E___O_F_F_S_E_T___B_I_T_S_=_6_4 calls ssttaatt() on a file whose size exceeds
              _(_1_<_<_3_1_)_-_1 bytes.

       The following additional errors can occur for ffssttaattaatt():

       EEBBAADDFF  _d_i_r_f_d is not a valid file descriptor.

       EEIINNVVAALL Invalid flag specified in _f_l_a_g_s.

       EENNOOTTDDIIRR
              _p_a_t_h_n_a_m_e is relative and _d_i_r_f_d is a file descriptor referring to
              a file other than a directory.

VVEERRSSIIOONNSS
       ffssttaattaatt() was added to Linux in  kernel  2.6.16;  library  support  was
       added to glibc in version 2.4.

CCOONNFFOORRMMIINNGG TTOO
       ssttaatt(), ffssttaatt(), llssttaatt(): SVr4, 4.3BSD, POSIX.1-2001, POSIX.1.2008.

       ffssttaattaatt(): POSIX.1-2008.

       According to POSIX.1-2001, llssttaatt() on a symbolic link need return valid
       information only in the _s_t___s_i_z_e field and the file type of the  _s_t___m_o_d_e
       field  of the _s_t_a_t structure.  POSIX.1-2008 tightens the specification,
       requiring llssttaatt() to return valid information in all fields except  the
       mode bits in _s_t___m_o_d_e.

       Use of the _s_t___b_l_o_c_k_s and _s_t___b_l_k_s_i_z_e fields may be less portable.  (They
       were introduced in BSD.  The interpretation  differs  between  systems,
       and  possibly on a single system when NFS mounts are involved.)  If you
       need to obtain the definition of the _b_l_k_c_n_t___t or _b_l_k_s_i_z_e___t  types  from
       _<_s_y_s_/_s_t_a_t_._h_>,  then  define __XXOOPPEENN__SSOOUURRCCEE with the value 500 or greater
       (before including _a_n_y header files).

       POSIX.1-1990 did not describe the SS__IIFFMMTT, SS__IIFFSSOOCCKK,  SS__IIFFLLNNKK,  SS__IIFFRREEGG,
       SS__IIFFBBLLKK,  SS__IIFFDDIIRR,  SS__IIFFCCHHRR,  SS__IIFFIIFFOO,  SS__IISSVVTTXX  constants, but instead
       demanded the use of the macros SS__IISSDDIIRR(), and so on.   The  SS__IIFF**  con‐
       stants are present in POSIX.1-2001 and later.

       The  SS__IISSLLNNKK()  and SS__IISSSSOOCCKK() macros are not in POSIX.1-1996, but both
       are present in POSIX.1-2001; the former is from SVID 4, the latter from
       SUSv2.

       UNIX V7 (and later systems) had SS__IIRREEAADD, SS__IIWWRRIITTEE, SS__IIEEXXEECC, where POSIX
       prescribes the synonyms SS__IIRRUUSSRR, SS__IIWWUUSSRR, SS__IIXXUUSSRR.

   OOtthheerr ssyysstteemmss
       Values that have been (or are) in use on various systems:

       hex    name       ls   octal    description
       f000   S_IFMT          170000   mask for file type
       0000                   000000   SCO out-of-service inode; BSD
                                       unknown type; SVID-v2 and XPG2 have
                                       both 0 and 0100000 for ordinary file
       1000   S_IFIFO    p|   010000   FIFO (named pipe)
       2000   S_IFCHR    c    020000   character special (V7)
       3000   S_IFMPC         030000   multiplexed character special (V7)
       4000   S_IFDIR    d/   040000   directory (V7)
       5000   S_IFNAM         050000   XENIX named special file with two
                                       subtypes, distinguished by _s_t___r_d_e_v
                                       values 1, 2
       0001   S_INSEM    s    000001   XENIX semaphore subtype of IFNAM
       0002   S_INSHD    m    000002   XENIX shared data subtype of IFNAM
       6000   S_IFBLK    b    060000   block special (V7)
       7000   S_IFMPB         070000   multiplexed block special (V7)
       8000   S_IFREG    -    100000   regular (V7)
       9000   S_IFCMP         110000   VxFS compressed
       9000   S_IFNWK    n    110000   network special (HP-UX)
       a000   S_IFLNK    l@   120000   symbolic link (BSD)
       b000   S_IFSHAD        130000   Solaris shadow inode for ACL (not
                                       seen by user space)
       c000   S_IFSOCK   s=   140000   socket (BSD; also "S_IFSOC" on VxFS)
       d000   S_IFDOOR   D>   150000   Solaris door
       e000   S_IFWHT    w%   160000   BSD whiteout (not used for inode)
       0200   S_ISVTX         001000   sticky bit: save swapped text even
                                       after use (V7)
                                       reserved (SVID-v2)
                                       On nondirectories: don't cache this
                                       file (SunOS)
                                       On directories: restricted deletion
                                       flag (SVID-v4.2)
       0400   S_ISGID         002000   set-group-ID on execution (V7)
                                       for directories: use BSD semantics
                                       for propagation of GID
       0400   S_ENFMT         002000   System V file locking enforcement
                                       (shared with S_ISGID)
       0800   S_ISUID         004000   set-user-ID on execution (V7)
       0800   S_CDF           004000   directory is a context dependent
                                       file (HP-UX)

       A sticky command appeared in Version 32V AT&T UNIX.

NNOOTTEESS
       On  Linux,  llssttaatt()  will  generally  not  trigger  automounter action,
       whereas ssttaatt() will (but see the description of  ffssttaattaatt()  AATT__NNOO__AAUUTTOO‐‐
       MMOOUUNNTT fag, above).

       For  pseudofiles  that are autogenerated by the kernel, ssttaatt() does not
       return an accurate value in the _s_t___s_i_z_e field.  For example, the  value
       0  is  returned for many files under the _/_p_r_o_c directory, while various
       files under _/_s_y_s report a size of 4096 bytes, even though the file con‐
       tent is smaller.  For such files, one should simply try to read as many
       bytes as possible (and append '\0' to the returned buffer if it  is  to
       be interpreted as a string).

   TTiimmeessttaammpp ffiieellddss
       Older  kernels and older standards did not support nanosecond timestamp
       fields.  Instead, there were three timestamp fields—_s_t___a_t_i_m_e, _s_t___m_t_i_m_e,
       and  _s_t___c_t_i_m_e—typed  as _t_i_m_e___t that recorded timestamps with one-second
       precision.

       Since kernel 2.5.48, the _s_t_a_t structure supports nanosecond  resolution
       for the three file timestamp fields.  The nanosecond components of each
       timestamp are available via names of the form _s_t___a_t_i_m_._t_v___n_s_e_c, if suit‐
       able feature test macros are defined.  Nanosecond timestamps were stan‐
       dardized in  POSIX.1-2008,  and,  starting  with  version  2.12,  glibc
       exposes  the  nanosecond  component names if __PPOOSSIIXX__CC__SSOOUURRCCEE is defined
       with the value 200809L or greater, or __XXOOPPEENN__SSOOUURRCCEE is defined with the
       value  700 or greater.  Up to and including glibc 2.19, the definitions
       of the nanoseconds  components  are  also  defined  if  __BBSSDD__SSOOUURRCCEE  or
       __SSVVIIDD__SSOOUURRCCEE  is  defined.   If  none  of the aforementioned macros are
       defined, then the nanosecond values are exposed with names of the  form
       _s_t___a_t_i_m_e_n_s_e_c.

       Nanosecond timestamps are supported on XFS, JFS, Btrfs, and ext4 (since
       Linux 2.6.23).  Nanosecond timestamps are not supported in ext2,  ext3,
       and Reiserfs.  On filesystems that do not support subsecond timestamps,
       the nanosecond fields are returned with the value 0.

   CC lliibbrraarryy//kkeerrnneell ddiiffffeerreenncceess
       Over time, increases in the size of the  _s_t_a_t  structure  have  led  to
       three  successive  versions  of ssttaatt(): _s_y_s___s_t_a_t() (slot _____N_R___o_l_d_s_t_a_t),
       _s_y_s___n_e_w_s_t_a_t() (slot _____N_R___s_t_a_t), and _s_y_s___s_t_a_t_6_4_(_) (slot _____N_R___s_t_a_t_6_4)  on
       32-bit  platforms  such  as  i386.  The first two versions were already
       present in Linux 1.0 (albeit with different names); the last was  added
       in Linux 2.4.  Similar remarks apply for ffssttaatt() and llssttaatt().

       The  kernel-internal  versions  of the _s_t_a_t structure dealt with by the
       different versions are, respectively:

       _____o_l_d___k_e_r_n_e_l___s_t_a_t
              The original structure, with rather narrow fields, and  no  pad‐
              ding.

       _s_t_a_t   Larger  _s_t___i_n_o  field  and padding added to various parts of the
              structure to allow for future expansion.

       _s_t_a_t_6_4 Even larger _s_t___i_n_o field, larger _s_t___u_i_d  and  _s_t___g_i_d  fields  to
              accommodate the Linux-2.4 expansion of UIDs and GIDs to 32 bits,
              and various other enlarged fields and  further  padding  in  the
              structure.   (Various  padding bytes were eventually consumed in
              Linux 2.6, with the advent of 32-bit device IDs  and  nanosecond
              components for the timestamp fields.)

       The  glibc  ssttaatt()  wrapper  function hides these details from applica‐
       tions, invoking the most recent version of the system call provided  by
       the  kernel, and repacking the returned information if required for old
       binaries.

       On modern 64-bit systems, life is simpler: there  is  a  single  ssttaatt()
       system  call  and  the kernel deals with a _s_t_a_t structure that contains
       fields of a sufficient size.

       The underlying system call employed  by  the  glibc  ffssttaattaatt()  wrapper
       function  is  actually  called  ffssttaattaatt6644()  or, on some architectures,
       nneewwffssttaattaatt().

EEXXAAMMPPLLEE
       The following program calls ssttaatt() and displays selected fields in  the
       returned _s_t_a_t structure.

       #include <sys/types.h>
       #include <sys/stat.h>
       #include <time.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <sys/sysmacros.h>

       int
       main(int argc, char *argv[])
       {
           struct stat sb;

           if (argc != 2) {
               fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
               exit(EXIT_FAILURE);
           }

           if (stat(argv[1], &sb) == -1) {
               perror("stat");
               exit(EXIT_FAILURE);
           }

           printf("ID of containing device:  [%lx,%lx]\n",
               (long) major(sb.st_dev), (long) minor(sb.st_dev));

           printf("File type:                ");

           switch (sb.st_mode & S_IFMT) {
           case S_IFBLK:  printf("block device\n");            break;
           case S_IFCHR:  printf("character device\n");        break;
           case S_IFDIR:  printf("directory\n");               break;
           case S_IFIFO:  printf("FIFO/pipe\n");               break;
           case S_IFLNK:  printf("symlink\n");                 break;
           case S_IFREG:  printf("regular file\n");            break;
           case S_IFSOCK: printf("socket\n");                  break;
           default:       printf("unknown?\n");                break;
           }

           printf("I-node number:            %ld\n", (long) sb.st_ino);

           printf("Mode:                     %lo (octal)\n",
                   (unsigned long) sb.st_mode);

           printf("Link count:               %ld\n", (long) sb.st_nlink);
           printf("Ownership:                UID=%ld   GID=%ld\n",
                   (long) sb.st_uid, (long) sb.st_gid);

           printf("Preferred I/O block size: %ld bytes\n",
                   (long) sb.st_blksize);
           printf("File size:                %lld bytes\n",
                   (long long) sb.st_size);
           printf("Blocks allocated:         %lld\n",
                   (long long) sb.st_blocks);

           printf("Last status change:       %s", ctime(&sb.st_ctime));
           printf("Last file access:         %s", ctime(&sb.st_atime));
           printf("Last file modification:   %s", ctime(&sb.st_mtime));

           exit(EXIT_SUCCESS);
       }

SSEEEE AALLSSOO
       llss(1),  ssttaatt(1),  aacccceessss(2), cchhmmoodd(2), cchhoowwnn(2), rreeaaddlliinnkk(2), uuttiimmee(2),
       ccaappaabbiilliittiieess(7), ssyymmlliinnkk(7)

CCOOLLOOPPHHOONN
       This page is part of release 4.10 of the Linux  _m_a_n_-_p_a_g_e_s  project.   A
       description  of  the project, information about reporting bugs, and the
       latest    version    of    this    page,    can     be     found     at
       https://www.kernel.org/doc/man-pages/.



Linux                             2017-03-13                           STAT(2)
