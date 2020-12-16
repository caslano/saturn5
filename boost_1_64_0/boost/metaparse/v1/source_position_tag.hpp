#ifndef BOOST_METAPARSE_V1_SOURCE_POSITION_TAG_HPP
#define BOOST_METAPARSE_V1_SOURCE_POSITION_TAG_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/source_position.hpp>
#include <boost/metaparse/v1/fwd/get_prev_char.hpp>
#include <boost/metaparse/v1/fwd/next_line.hpp>
#include <boost/metaparse/v1/fwd/next_char.hpp>
#include <boost/metaparse/v1/get_col.hpp>
#include <boost/metaparse/v1/get_line.hpp>


#include <boost/mpl/int.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      struct source_position_tag { typedef source_position_tag type; };
      
      template <>
      struct get_col_impl<source_position_tag>
      {
        template <class P>
        struct apply : P::col {};
      };

      template <>
      struct get_line_impl<source_position_tag>
      {
        template <class P>
        struct apply : P::line {};
      };

      
      template <>
      struct get_prev_char_impl<source_position_tag>
      {
        template <class P>
        struct apply : P::prev_char {};
      };
      
      
      template <>
      struct next_char_impl<source_position_tag>
      {
        template <class P, class Ch>
        struct apply :
          source_position<
            typename get_line<P>::type,
            boost::mpl::int_<get_col<P>::type::value + 1>,
            Ch
          >
        {};
      };

      template <>
      struct next_line_impl<source_position_tag>
      {
        template <class P, class Ch>
        struct apply :
          source_position<
            boost::mpl::int_<get_line<P>::type::value + 1>,
            boost::mpl::int_<1>,
            Ch
          >
        {};
      };
    }
  }
}

#endif


/* source_position_tag.hpp
w/GJ3/z4c+p53vb+GKZPcLINniegrJq37anLoq7iys6t17HhtppkzrWxDvk8i2m/eYTj75pXoU8Kfc6vV/USTqjPNtY78Zofbx/VPvnfQt63Hus4tDUVwNso1k/zOm4/lo3qN+/DVoWyLRE4VFfsnG4Z5N8vPE/IY+qOoGnm6CsEzVGMg33TEGeVwLm/WtfbAzoHCN1gDQFaWjcHRbqBDl2+tQurm0O4DOmvuDKfyVNmoECZw0z7kj6Ap/eRDzd4JYwH3YZ4Hcqu8tPrUnj56a1RuitOpnXcH1GG53C2rO2PR3BZ4mvLyvZoXlG2MK99qs2KKzNAZeLPArjohxSdj6JxtrfyDpHMxT4R1or8jQTjnlqf2v2JDPsq8Gf29rhNCc59ZsDcE16vxxCsRxBf1YzjGw0u3lyCj9G4x8IPHIJzLpLX4+u1Xz2B6RIM92ET8ePYiShLdMzcAXpQ+4i67Mn1+l5vOb/JQ3LErz9PRZkyxKP/OJWR6W15Pkt2Vlgnm6CTQT9fwzmi+pjzufV6rXIG64dghdfxZ7GvFLhapnNADzwXbPPzmBeU1b7n99W6nSjt7err9Zy2Z8Bd3uVmr/qCesgPuHqLCrQuN+ePJ4/W5493h61xHw7ruaS+sK++1PT71WM379+/TWXyfYO/yX/vcd/5M8EB+N5zeb383rM0nc10pgbS7Q6pe013p4+lkD5qyMVd936iIAb5DNkGy6o0jwFiMn2vXp/9JDzAQ53/APZ4fDXvcf4QtinpX6nnI4QT0r/K2MKBho/pmLf8yPBBeAx3cRUJHhsL9f+gJyfTT+pZvuti5LveyHcd5LvByPf2RMaT95JuMnifhR5srK5btB4ID3C0x22GzsHjNZ0LUN9PDd7TEzTeY6NDvDvUuJ7fTu5SePnb+26Fl7+9f6Hw8uv3XoWXX7+/Unj59Xu/wsuvlwewhp4mztb/jvJsrIMHzTj1kJlTBEX4iUfqNc1xhuZjBn5utYY/buqcXrX5Ov9gaF5n6nxS0SzO3z1laJ451uwFRnDo3uruOeVji9PdC4am1d1fDNzq7m+qzuJ096KhaXX3TwO3eniJ4PFnGPo7MwPeS7WHN86jGaHNF+89wSaPwThz+URHx6Hum7vD/kp9NNasjO6xi3MZ2XXdmdWIEy5j1vXRNVad/7p/eyRDl7V70m0b6IF9d04iE7yyCPdsXxXjV0UoS4jcPpjODBBqWspjYfgeCjmSvl93ZzJD6cGo/st2cHLQ9WP3Xj/1yUXRfWM5bqLe9ODRLgY4kHW9Fkb1mjMgg7l44qu6e5VeEgK2Ip3K0EGRVxaAjzeH8+GQj6S3pLpF/GsD4PjXa8DDrnniD1a79oJOltJBv4WE4XkDrBIwCvPtQVF+MiCRu1M9S4d6O9z5kjmIP/i24Hd3YXvdXcyqzCMu4+/5fwhZ/V0w2C50H76BFazt70cch3c9fyhNZRhnqO/Ivv71fZRHZyIpNxj5Xv2WnYm0cfffr+czkfPQnh/I9tzCvjlX2ROd+Vw92KPtiPKoQXRfpDxncO7tGZwrChrEuaKQB0IyTYQsfreGfYHT31GtxF3AfTiBPrzCTYEyWe7KhBPJPqJhmOz9fdRZwyJcuc7HWlX14Y6NZKvch5BHNpp7OzPR8NHabqsGbruoL44cxj8cTVd60GqPAazDBaovunenqG0H09whZbsxPIjm9qWY20dnikcJfsrgo1DIekXkwo4K9bejVF8zmQViGGxB/f5bVgPiw0An23pZsh0ZGFCki9IGL9uA842pnpU5nURvl2/XYMeHOHvStrSg8DmsZa0rl7cvW9q2om1/TyAOkPM320OOjgLn/Z4Y42wJLPQ7Nxs=
*/