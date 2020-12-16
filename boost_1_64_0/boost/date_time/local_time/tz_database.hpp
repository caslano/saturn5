#ifndef BOOST_DATE_TIME_TZ_DATABASE_HPP__
#define BOOST_DATE_TIME_TZ_DATABASE_HPP__

/* Copyright (c) 2003-2004 CrystalClear Software, Inc.
 * Subject to the Boost Software License, Version 1.0. 
 * (See accompanying file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include <string>
#include "boost/date_time/local_time/custom_time_zone.hpp"
#include "boost/date_time/local_time/dst_transition_day_rules.hpp"
#include "boost/date_time/tz_db_base.hpp"


namespace boost {
namespace local_time {

  using date_time::data_not_accessible; 
  using date_time::bad_field_count; 

  //! Object populated with boost::shared_ptr<time_zone_base> objects
  /*! Object populated with boost::shared_ptr<time_zone_base> objects
   * Database is populated from specs stored in external csv file. See
   * date_time::tz_db_base for greater detail */
  typedef date_time::tz_db_base<custom_time_zone, nth_kday_dst_rule> tz_database;

}} // namespace

#endif // BOOST_DATE_TIME_TZ_DATABASE_HPP__


/* tz_database.hpp
7y88X38X9xfozHLTZ8z9P7fk7v8RcRTkpYa9II2mJlB80D0wtM7rlWKoV3EhswY0oyxoVoEphF9O+ph9UXkqlgX4uI7jWziVlrYzFvCromKQHW/spKB75TVZXK1YCsaqwCVPmC8wzy15cPfDpyxnruj2wijiNoN2Wb1WdbZ5eEQBaSLuN8xKULG/m3OOaggsHmHca7PjKXe9Q82ksbc2A+2GjLAmIyxYAm2o6nzTdnZIAmvRjcYcSUajISMMZDjUbKQZme+DFToSvma81QSLenOciD8pjsPAt+Rfeiq0FiYymH58KhkQEssX4Oe17icAJqd4mwlzKhyY96nxD8sleZHKhswb4MHxcfUfdb76MHnYUUkac3/QTnIBDgFjRtslH8VPKsGH4MHocf7teOCj6z07r7nLzztuEPKTlQd/7CgkP5friNvpWi0/75xnl58XS/kJ8E5uKiA/V+lwU7fWGvl5rZGfo5XBCyYXB/3cRdez1OzQ9DTWstT8wZ1DLTUd+dcKFH5sLfMvYYkbjVi5b26LxdXzfmD3og9n2B1s+jqMYl2th+SFEN6KX943n/36OGUipURMykhMkdLzeTqbeSPJ4nbjh/dCGx9h9XHSL2/kk5eGsovVNpw/m8xyn0Nj1P5KbcnAU+770rMlkv7VNSyM5/qcQxc5wVLL32kbt+yEIbHssgQ1jFtAwwigX80qg9e9kO9arpHLPQXlQKaKzPdfQJlfhTORC0Cv7/eKDnj8bNZhcMo3KKXZpNyKKVJLcrZXsEndj3BcfbdpYI2HgkleR5gP8Rqy5aG3mUspf6TKh/4Acn+rRJNwsrpyOTM47RkMg3G+uKHHKsi34KeIgDUex3LsIbazlcqd65H3VcMsQTiZ6axmHHUa1ZjhoZMCAu3d51HmPpTZKBSIHZy5E0bjPqq7YAqHpvICoHYtjuARYNWZUbXmcjM59HdixsEgZM7WQmZmDQiZS0HIXGeEzLcuV8uTW91ZA7DKWmmlmwICoyLnj6xRPJu+A0icdy2iRvl2rkb98N6AOpWPeoZCnZ1E0Ojzu2WZ2YTJyUtHr2+kyWvFU61DI9n+P34F5r92p/lvZaH5b7xXz3+jaP47ufj8d1aB+S/o1fPfKDP/tefmv5Tr/LdoMc9/UzQ9jaPM/PeFd2X+i+D8dx3zry63f7xrA+8fP/khuX8ESZnwkYdhR1RdbqQPlYfSV9/Kcm26yO/vFRpZfMbzBlVrnpFuFnFeu/akZytVYZW61vibVcALSOqLsOoFyo3G8Es9GdVXL6ty+6yEcpj0clio1WTRmVT0rFzRkEvRMBU9NFc06FJ0OhX15YrWuhQNUdEX9zJFq12K1lHRb+WKBlyKBqnoNVB0hFIBqiKdiXIPLblDtOR2YvJ4YvIJexVmci2hmLhXUSbXUNG3RhZlcjUVfWZkUSZXUtHbRxZlcoCKLhpZlMl+KhofWZjJVGwSFCMGb3nZxt7MAXATgPka8FtY3RDAv+kLlbA3E2lITyzVi4VVui7n9r3+g/jJ1+2KcuU98Ctw/vkaB/lesayQfO/XVt5ApZbvT51QVL5/4vQC8t1H8/8II99X5+b/S1zl+1dWsXwv1/ub1hEs37O3vCvyHfm3fLngn81pqQk3NXvDUhUonrmOdjTZpXqd+MXb+Jh586l2HibyIeEiFSYDaN9pTdKNodnoH5rsPBp3reaRRrLu1CFjS8yJFZdfbVOVAgm3rcCVHjgmsu98kmeuOpy56vSzanidmrk+T2OtDquDUEWHQK8ytnWZG+qgTXCT+NG0tmfrDM6hS87Mrw8KE3Gn3VRYXaMZY9+FqljUp+oZ2dS42n+9zTcYjEGAL7s+cyqsrrk=
*/