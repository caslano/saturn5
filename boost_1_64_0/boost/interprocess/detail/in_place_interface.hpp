//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_IN_PLACE_INTERFACE_HPP
#define BOOST_INTERPROCESS_IN_PLACE_INTERFACE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/detail/type_traits.hpp>
#include <boost/container/detail/type_traits.hpp>  //alignment_of, aligned_storage
#include <typeinfo>  //typeid

//!\file
//!Describes an abstract interface for placement construction and destruction.

namespace boost {
namespace interprocess {
namespace ipcdetail {

struct in_place_interface
{
   in_place_interface(std::size_t alignm, std::size_t sz, const char *tname)
   :  alignment(alignm), size(sz), type_name(tname)
   {}

   std::size_t alignment;
   std::size_t size;
   const char *type_name;

   virtual void construct_n(void *mem, std::size_t num, std::size_t &constructed) = 0;
   virtual void destroy_n(void *mem, std::size_t num, std::size_t &destroyed) = 0;
   virtual ~in_place_interface(){}
};

template<class T>
struct placement_destroy :  public in_place_interface
{
   placement_destroy()
      :  in_place_interface(::boost::container::dtl::alignment_of<T>::value, sizeof(T), typeid(T).name())
   {}

   virtual void destroy_n(void *mem, std::size_t num, std::size_t &destroyed)
   {
      T* memory = static_cast<T*>(mem);
      for(destroyed = 0; destroyed < num; ++destroyed)
         (memory++)->~T();
   }

   virtual void construct_n(void *, std::size_t, std::size_t &) {}

   private:
   void destroy(void *mem)
   {  static_cast<T*>(mem)->~T();   }
};

}
}
}   //namespace boost { namespace interprocess { namespace ipcdetail {

#include <boost/interprocess/detail/config_end.hpp>

#endif //#ifndef BOOST_INTERPROCESS_IN_PLACE_INTERFACE_HPP

/* in_place_interface.hpp
6gaGcYfvUXtp3Kk5dCvcQgzy/SDuozSDFdc9R3yVxRjfu6LMLgNEz4/iHsp69Nwd8Zh+JgVE8w6Uh88BvifGKmVgP4mx9jjON9AMzmTIdsg2kQTPvdoDy+rlt777Yp7ENHjK6/sjPI2UyQNxnywTiNODcR/WRArrobhH5CutrY77XB79LM5hvbqplOB5RHvE0gmam+B78PdGq44rZSgffx54uB3THIWAl+vZVy4M/7EoK6T1ZsvtafS478Ho0b1/6TOexUv14ImAZ9Oosw2zIHoUxq98D7cF4r/2uSqL3wR8PLHL4JA/GeHQ+KnMn4pwSAgfX4RnHnfwwcOIwnqmk6dcp/qI3yqf7eBzGcjroXHddtxPM/gwzOc6edIgTMqX5yN+efb5CzGe6nx5saOP8+WlqEfmC+1VHvdRm8B0vhL36Lyj7zC/6+D3KyPe/9Wol/KZ0vJaBw9XXJorEfXFyoPWkAd+8yzGs5h9Ha8yDwEIg8ryzcCTcjuENvwHn9PUJlpb7hgUBPjf8jU6EYLmN0SYPUvtbZ/12f3p3tG6WzPzZ5/RQVzI3rWsN8kOjJkm9/L7i88wjpSX7/nMxeN9X/fu9QEz6DxggLQnuWKUaLr2bwGHGxL7e4TZtcX/CBhGiPYmdwy+RuHacl/zyuXfinG5/MdnLj8+1Lq5BNO83Coeyw6x8O63vOYu3BV8RsnCcFf02TyYHwwhI18pxiFk5CtbnuvvGejNqf7iKpp765xWVZz7RKvFWHsc2OqO1VRdXIOZqotr+szl0Vqsq7q4NjNVF9dhFq2L6zJXdXE9Zqourh8wjBDecwPL5vSGfXi4dkPmsjyAbRRh9p4bB0zOCdokYHIOz6YBGy/jNZspnX9Tbu4zt35ti0Dno54wzC2Zyz4qXLuVz/hVRe/GrSO8DflaGK1RGNuwJ+gDIt/W53w9xe8jzEXfD/NpO2bUt8Mwt2c96PPhdTsw9+b77sg697OI7cRM9bF2Dpn8cQXRxfzahX2qH+b2Do94oFIR/1iEQ8UivmuMj/LzZ7co5/LYXXHqH1B/Y484b7RpL1pILuXLnjGvqWAwpgY+vOfHlc9VJMj7vZirftykkKXxvO9SPp33k6Mezvu9o5zzforift7vE+Wc9/sq7uf9VMU75/1+yhvP+/2Vz8/7A5jDs0POGz+QGYZJ+kGso530T5AOi2PEOVwHS12cw3WI1Qen5cI+V7dkxepYNm7k9gqPMIgIhdsjOdcBnAsgGEyfIT0ndVM/rX+61FPen3AG6fDZemrXoJmXD/pMpxulCyDEqU/q7m2B6Tk0ynhez6yQw4ML2WzF+AzaOSGjVTpJ0nRrq/o7eOw5qgOaiwaIYQxGPfwd97AYh+uxLg8pzkvRsnnNdWrj+aiv3kiacGQf3Gs49MB8fMhryK+5ivMa83kxJs7UPDzksGxfRhTjOV/7VJ4tiHo4z46Icr7+SM1bTZHOoyTns6IgfkdLps+lAs8xnT1msAg9hbiHzqPCeBwrPfirzhj3guuLUWZadKWYuj0BlAee2MBKikGLhvwpx1mWS3BtojjvpTyqmaloGOexOKPSp7H7qIfOsKJ0VZSHv6sfp5h7EwFfFOX83b4a55VWgt/3xqPcfZYDTy3uoVmP6KlrDy9nondaI+oJd5ehsfzAK9dRNiWD3aYLFfvsTiWDEFFvSR3XKOEYfqhH9tZaLD1Q5YSJ4nSC9AR7FS+JMLn/0NIor1fLdP0yyeUZbnTvEwNuysW98z8ZYXhrOps8wrHkksSGf5L0BHv3nhywMG2naE5po3PLJYdqi/ppUodmhXH5tNJhng6wzyjGc3RO1ywHK+jo2jM0N4PIyD6rGFReYGc=
*/