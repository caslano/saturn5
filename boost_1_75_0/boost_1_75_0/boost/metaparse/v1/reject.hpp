#ifndef BOOST_METAPARSE_V1_REJECT_HPP
#define BOOST_METAPARSE_V1_REJECT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/reject.hpp>
#include <boost/metaparse/v1/fail_tag.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class Msg, class Pos>
      struct reject
      {
        typedef fail_tag tag;

        typedef reject<Msg, typename Pos::type> type;
        
        typedef Pos source_position;
        typedef Msg message;
      };
    }
  }
}

#endif


/* reject.hpp
CaxCyeRDEMf8hPu90SSObSRxDEPMNHEZxbF4kFFNUfDFp2xozMvrhh+UqQhMIosmDvfgAhLJ2HcT2Xd5yedkSLBIBHyZ7iSU7TpuUzaiTHYLa/WedJTJmCTvVBtBjtthUiH2oArhxWBkqbrvobeyk/N0LsTqQog9CVrFYSGQ/YBkn1NDbKIG6Qyl2YEo5uaAeFNDgnsVj87sjHLuSSrMS0K5o6ieLHH1Ioo26KzVyMggGlovGlpv6DoF9bDuU+CkS60BwOeS11DghZX0B64krEs3E2x5Q6f84fe6ym0WIa1KWJ2qDCGtRpyrMbwDjiKbWfRs/AN9Tf/1i8yi60YuC+ZsFCLmyabxUnr9O2xOlwIxdGcTJmhQiq8bxas3GuIrI4qzjlF137DLYbktpLzALfuNBguBNscQaLlFhAmqjQNOMF5Row0o4PUv50ue8fMsOpU8n46R/JbP+fmE+RhVCqQ59KiNK9X1s+nicc7U/5gncCHMWb/zDiSTP7fkIim+gUsRLCaBW/tl8EKauYOPpAceKUlXIbqDHar5Av4wWlEC6yhEzgo9ruGyw4JlL7GbhtJNTD9HIGxR5bcdANgBj3L+NDaa86cQAFiObFsppUD0RqXcjk6qdRxSGDHRog0EcZOFsBe8V+ApS8xlvDeB30v87XAnYF2r8ayr8GSEo/g1hR4h9BkLBi4ty8860UBwcFiC936NaYmo7zbu
*/