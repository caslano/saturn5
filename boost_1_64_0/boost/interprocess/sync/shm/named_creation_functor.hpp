//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2007-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_SYNC_NAMED_CREATION_FUNCTOR_HPP
#define BOOST_INTERPROCESS_SYNC_NAMED_CREATION_FUNCTOR_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/detail/type_traits.hpp>
#include <boost/interprocess/detail/mpl.hpp>
#include <boost/container/detail/placement_new.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

struct named_creation_functor_no_arg{};

template <class T, class Arg = named_creation_functor_no_arg>
class named_creation_functor
{
   typedef named_creation_functor_no_arg no_arg_t;
   public:
   named_creation_functor(create_enum_t type, Arg arg = Arg())
      :  m_creation_type(type), m_arg(arg){}

   template<class ArgType>
   void construct(void *address, typename enable_if_c<is_same<ArgType, no_arg_t>::value>::type * = 0) const
   {  ::new(address, boost_container_new_t())T; }

   template<class ArgType>
   void construct(void *address, typename enable_if_c<!is_same<ArgType, no_arg_t>::value>::type * = 0) const
   {  ::new(address, boost_container_new_t())T(m_arg); }

   bool operator()(void *address, std::size_t, bool created) const
   {
      switch(m_creation_type){
         case DoOpen:
            return true;
         break;
         case DoCreate:
         case DoOpenOrCreate:
            if(created){
               construct<Arg>(address);
            }
            return true;
         break;

         default:
            return false;
         break;
      }
   }

   static std::size_t get_min_size()
   {  return sizeof(T);  }

   private:
   create_enum_t m_creation_type;
   Arg m_arg;
};

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#endif   //BOOST_INTERPROCESS_SYNC_NAMED_CREATION_FUNCTOR_HPP

/* named_creation_functor.hpp
fPqNOhVZZXPQNeVTvkvhJVjofOUqH+28pjEl/e51x4J6S7hJYjE11LwHLXH72mHRTcZyUF3lsbf5Ig4ipwsX/UjLtCcNOjLIM0B0MqzwPdRD7jMMdvJx7mEzblw7r701r742rWl3yxR93VBziZ0ntUe60X7fCivT1SuWL6pkpA5bAee7PaDf7cb3LE+5rW7SXURwY7l5dWf3krrGZdx9lyrlfH/j+JuGDfvudfeCuVnOX8VeG3HGsTgN7xvHMI3FeXXvyJJRzkWVi9y9Yu7T+jTOs9/vQO7dmchZhnuYGGE/LLtse0vZuvdvtfhJGTpjRZSVtJPQfU5u9j2uY0S+cQW3Pz+mG12XU8lsj2Xg/D74e+590aKyotVliypLpFWVryytFJZVX3ll6/jMvyTsgoBd3luta60zA2eZ+0EtS3/7dPd3zviVrTOdtA1wxn+GiV+2vx754lT+H4nVHQe55jUZ13TGMeeJ+x3Kpav1Y1rg76wuxnGpdPvbS3R7ORxOqZKW8YQcYdzbIF7O99D8UKIS/nOsbbxReIOOMS63Uvx+792Hxam7n5NzD1nrrN7K0RSKo97KwPdL1nCn3ltuvZdyekT0bmN7lUHOmO/XxC8JnVCYRStukse8O578UdGZxGhylpSR7MQofusp4z7WMFZYXy1xXihjjU3p+RW6l/ZaQCFtp10MsvuzuJykpKTlCXHBXsmefsx8v4nrOHH1kbgmByZaXZz7NUvKMN4pkwzRucgabSU6ZVIkfr+z8iiT72qZuH21298HRW8uuevCCHSM9NM7iHR9lvbTSdP9/bTqbENngOiM9fXTtvTT/Ddm6ZhzbNX9wcTEYOxVwcQ4y8xxFCqzOdlNZRZb9ZOEhNhkf5mhd4h4h2WH0ll1xJdO1SnIDqWz6hemdKbrNdehN1jGxqseC8Ym+fcvU70t6KU37auWHz5uavdnyVHsj+n2P/pebXhOed+rd/VTe2UulgROBxfY3xS/MvVLq1eVrJQuydcnhfjdftfUZwTeJZcpgXjzd8avWpzHcfesFL1xgVRC9Q/EwRVgnkNy49N3fd98hv9ZpmG8fYlTd/8o53oHTlAi3QNN8zJ5Ulok0NN+MxptvVnyhKddydh/gfjtYqez5OZtv0Cy6LS1v8s1ujr93UoJN9FK1/6uKZ7H6HvKsNno6/QB/2zq5wK+vkjjWWKHI0xSC3G5z1T25l25yEnT3aI3wJkninld+wPq53Gba/Y0+joUg92dOuy2L9WpCOkEhgUTU4KB4ZH2G1T9Teg/KpxjBZaPc0x1djtx3mxv+Byo+mwL+9FqmKNOvFXVbrzNdZL7aRsP3h7ra+Oqk4fOEOFbq/qbO87QfA5iPNc5O9V9/5B5rDa21Wxpq8b5JzkXBM3zSu63SV6OvmOE5rSRufYY5utuWy6xv0wWVRrmk9z3uKWivwjbXuPencRnmid1n/sPv67Pbq1HN4r7Mp4E+WHPe/d9rlx0PszbY6xxf+Plmqb5nvdcS9/RQnW/SnQuoW/rpn6ha8+2uuIbul9DuUfDkOHIiNTW9x9qbc6o4Kwm5b/EcP/AP4Jz7Hc7T7nbs7OGeXdnrnbGr23dTTHMccIqWBJjKHfiM86Vm/pEdI3z3s77Uje53mJ3X1TRv6X5vqjm++zck69LHFZgu3Wp895jHbL94prvH6x5XPwbd148FXeOhC+wssVNiYi7JtCNEriCr6TXrUedfm+YnHsiplnd0Hi/KufuZoe9a5131yXiN86pXyXiLouJYWFZiqZ1i/gVB2J4h5a+3/E7D73bAhsDDzjls0z81xL2QuHae0jc1wTSAhP98/aahiskvxsDF7Mq4yFK5AWsBEPX/qc=
*/