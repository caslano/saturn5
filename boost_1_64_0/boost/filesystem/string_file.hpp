//  filesystem/string_file.hpp  --------------------------------------------------------//

//  Copyright Beman Dawes 2015

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  Library home page: http://www.boost.org/libs/filesystem

#ifndef BOOST_FILESYSTEM_STRING_FILE_HPP
#define BOOST_FILESYSTEM_STRING_FILE_HPP

#include <string>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/operations.hpp>

namespace boost
{
namespace filesystem
{
inline
void save_string_file(const path& p, const std::string& str)
{
  filesystem::ofstream file;
  file.exceptions(std::ofstream::failbit | std::ofstream::badbit);
  file.open(p, std::ios_base::binary);
  file.write(str.c_str(), str.size());
}

inline
void load_string_file(const path& p, std::string& str)
{
  filesystem::ifstream file;
  file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  file.open(p, std::ios_base::binary);
  std::size_t sz = static_cast<std::size_t>(filesystem::file_size(p));
  str.resize(sz, '\0');
  file.read(&str[0], sz);
}
}  // namespace filesystem
}  // namespace boost

#endif  // include guard

/* string_file.hpp
36tTJ1P9lBpV3sRWFngTifWTZYGZS3xb71pU7//oqOonHaE8pa76qnWVhk7D5DtVRVouEKFzsfcJ3dnwQdH7mJK/raPxC9EXGSJzIkuAruac07HYMS8glC9Ql8bykyfa7cD4djdzEvFuUFE9Eh/TffrmLdzso7Rr3B3ElDz8CHDAGi/a7EUkH/oT1YVb6wvKX1y+xmIDF+n+l9So9eO2qB/30dZPCeUnTaALWBEDckvH7k/APw5/p1Bv3bLFD1qOUAf9fS1oBHLr7yEHFnfcS/Xh1ToOiM2eTLGP9ycyPXe1h7QDCULr7doVBd4RFR5TyOTeaui4sIM4E2ccALTr+0StVFItDOjAm9oaqoeb74GmloYpC/cHWx7FuZ42Akvukba9N8uNwGZQskFpaPDaTfcHtuEMoNVQdG0K4844nmgpTUGTYWUHfcfmjV4xjjJmUa0n5aWYZY4D72fivu4w0z59JPww4Kc+gYcc/s64k084syD75idIgMtEJlvuM1UDWTpPuA7hJOc9e8kNM2ShFhWXByAOBEQs429ExqWZLCTu0shijbljk7qzdkpotGDOErrpgAqdFuKB9s0FMM4fV62kZf/dmkRVHbHXuvVe+gnM1qGu+vuU14LhmCYTw9VXu6Lf596TmDJf/wx/V9cxry0Hg2ERl48fhx2zIvUaMtarl2JWkVr7NHMrkMn1a2Zi7WFGUbSac7BbYcfVaZJhyMET2F5RR26z8gP2MHaDEEVcDBFm0glR+PT3VPis6GlGvyStCfNoxPALGfzOF2HgEuqi27YYDshmMfuWCk6MGjVmdlqGejOsOGbrpQaf2ol2U71k5/A4wEJZTzJz9G6qOFTyKKnnNsMfQvEBCnSN3s2Lod2a8f6IeP87Fx+Y29tmFyl1c7pywxLa1sHq5kbXA7gxyAn5WFj6jA7ZNN7oyZpGT6qJC2DwpTbxZzBy4I2Ekk6DJHPdfPyZZSNxiEYyI0NtJAPM6L4O4vDGqZTbUxB71I2kX/dWGsnZfwtSI6H8ft3FupE8liIayY4QIIBX5ZCokK86t9JIKhHvv3LJkOX56Jvb8aP7bjFwyOGIRotEJoo3pzrEAEUTLVlsXtaVsLxyLPHKsaRYu5usUocBoWF2Px9ShnzLhpSn7UQPkLwueT6NfAmFC1BHMSOX5cyAcDIhmgUv4ETiH8WrNR/TpsHnc8lzd0NkU3n6G75r0HymHMA2Q5zc7MPMlE/jhS8o4mRZqHkmvR0My5k5deW+SPMtYRNOchcx7W4SmamN8PYu6v1WOL87QuUszJLHwTQkr+mf0Ru7HgDMZQAR6+xkWS0eXi1YViwFVSZPTqO6dDYGiWp881hKNFTH64lNhMBOnqXICn4huYlttf/sDbiNv/xI5zs3xbE2L3umtPgQJT8ZtFDyQKMuxIx/hQuoBuAtCWJmZTaNxY7ScmuTHyKTpt2dxs1+4BOq8YfTeIPA8dEr86cxtfZVvQHiTai1OF6xQ6CO0AZlM20E0itjbZ1ub6Y30U18LrqZ5IP3guHj7R8gFvl6kIOGm296GixaiPV8XB6aRO+irmzS6UBLx8++DMa+dGwx/9nlVXp2fhudXVxERVJRLzueY+6pHnilhDg+Wnl32xBFWuIVixr1amvelRMctYsvcQvFeLy16HVSv56IDeRkWtncvB5XNotxZVMuVzapMFtKT4oeE5VMaCfS/11rdywa2GkHWj4+onNLxi+CZEZJtzBOIXbaM3ZyjexUwS7DTz9lmb/XD+FgLN9rc0ar38sR4Xu9t9/0vSb/o8X32vqq8r3OpQr6583ye1XICjov1Mr38nc4mu81K970vb74l+F7LSZ2ZjN2co3s7P0=
*/