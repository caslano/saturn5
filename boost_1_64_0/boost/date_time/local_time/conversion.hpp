#ifndef DATE_TIME_LOCAL_TIME_CONVERSION_HPP__
#define DATE_TIME_LOCAL_TIME_CONVERSION_HPP__

/* Copyright (c) 2003-2004 CrystalClear Software, Inc.
 * Subject to the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */


#include "boost/date_time/posix_time/conversion.hpp"
#include "boost/date_time/c_time.hpp"
#include "boost/date_time/local_time/local_date_time.hpp"

namespace boost {
namespace local_time {

//! Function that creates a tm struct from a local_date_time
inline
std::tm to_tm(const local_date_time& lt) {
  std::tm lt_tm = posix_time::to_tm(lt.local_time());
  if(lt.is_dst()){
    lt_tm.tm_isdst = 1;
  }
  else{
    lt_tm.tm_isdst = 0;
  }
  return lt_tm;
}


}} // namespaces
#endif // DATE_TIME_LOCAL_TIME_CONVERSION_HPP__

/* conversion.hpp
OGs68ErUT2JlagZcYSPJ4mVmgfEys0C/rBLSQLTEXqwQ73cWOM73LFA690bbuTcOdO5ZeYlRVbA8AAmofpeymmuUY/mHJsK4nBwJVOde+sKkdO5A0527cBIC3g/OCbQOYc/HJrOiJWNEOgS4rhFZWgESr69WZi3RKT3HgIj3t1Nz953GZQKpEoh+tigzZuTZopHPyGfkM/IZ+Yx8Rj4jn5HPyGfkM/IZ+Yx8Rj4jn5HPyGfkM/IZ+Yx8Rj5v/GcmnoNWj2jjBlLnzOn0iHbHerpqK7BgYn33tVj36NrzhO9MNF/jHjRf/Xs+fteBgWl5wTqnom+iWeXh+7k6Cq+Y1ZQl31FLvHLHXvlnaxGZKfdmLUD2EdqshPHfpmK44GeHfKEWD8yp1Symmy3d20KRWDDKlDxGq7PGd1rONuhqoSioIbESiBSH9ytqsrbn/YQaQPZNtHYJ479NxXDBbx/ywTS8aqWKg+m2l64GUiSKo7HkbTTJWkhnulFnOqwhcQ0JcXF438cuvJvKXcYOEN+uLo8ISVSTSqgvYAeerwvYgabKRT9+5PWQtsTXmUDJvet2D64uhiZdDBUakigtOikg7+t8ENlc7i4fgPhyHnlDRqKaVUJ9fw/wfN3fs6ykgDghCHg96CvxdSZQcm2P3cChi6FZF8NoDUkCYu/E7MjH1L2ZQEJcSu6bFcvkRPhuwb7Gv/X3i/mqWvKpoLet8j5RhciWcsepAOLzUfJaiUS1qIT6CBXwfB2hApoqbGEAAl4Px0p8nQmUnJzytF4tZa1XqqSwox6FXV1S2P09UtYrzbq6WSNfHRhZI/9v+sw0o4JYQ8kgoQmDhGOm0iDB7PaKBdCs5te200jhrCCNFKZdQiOFKy/BSOGG2zBSIJRzRk/L980MBwLoRHiU8Bl1yoc12DY7HZ1FtNgz/EMTmUK6Phf9+5QNa130+8RuRMYSJrQ/1XrAwO8zxhq5a7GXqhjFrwBU1nzrTj3oLUlweJIE/UgSt5LEWZK4liTkLUloeJKE/Egy1UoylSWZqiUJe0sSHp4kYT+SJKwkCZYkIQO7Fph6a0ezEsoi1CyhZigYjL356rvAvCMJ9TNm/p7AG6Js0212pnN2puvsRFV2OMTZQUiy099DuTkEXcFcpO7Y1PT/ZU1LTVEcpujHB5IpakAVNaDYpz1Cgzlnyl+29Zsyit9Tnp6XfcuA6GkuUdFEroxkoLWSf7ZHA21TYP46Dbiha1zdRRMD9d0nm8C6eebf2jCoHPbm7f3G4F0kFDraa/vbdqefm1O1AejE3tTt0ijJ2eu1bf1L822RafniZzJGYZsCrVARDJoao0Bpcj490chlcLhlyNhClKm5IZep4R88/sbw3VlmikJSSXsyRZN5ndXHszxbUBKTDrDliQ4D24RTEATZzAbaahp43DztkWn3OTX7G2Q0ySK1qSz9BmYq0FbRNzXEx7xRH221zu0JFztDke7srTMK9AzQXw0KOtXZ/s7XGL9R8DFJyVCCRiS4HwnIXLROYpRMtXPoPtvdOZJzVIJ+YURUXy2Uq5HyIkq5noZcgdY9CCaDNsMiCdilJTATBizBEY01/CPq3HHEdtRZRd/h1Kcak0HV3MBDboMHfU9JgmqRNerU7uMqybEmF9MDrTPZeibxTUYkYQCm7N4O/R0dJP096wLo72nQ30VWf79Svb2/bz3UtKLvNnyFiruZnnxHsGppA6wQZ940i+PkdyLQOoslSSV49skjflHSFJRUxK8uET9K3/2NSSN/qPiB4mHDTO50/tmoOtKOpqhijFXszVRnzrOTTNmw9olebGp5ndvBv+ujrGD+bdTAkNlEwOT+eJp6okDO3gv6igA=
*/