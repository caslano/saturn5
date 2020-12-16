// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
// Copyright (C) 2009 Sebastian Redl
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------

#ifndef BOOST_PROPERTY_TREE_EXCEPTIONS_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_EXCEPTIONS_HPP_INCLUDED

#include <boost/property_tree/ptree_fwd.hpp>

#include <boost/any.hpp>
#include <string>
#include <stdexcept>

namespace boost { namespace property_tree
{

    /// Base class for all property tree errors. Derives from
    /// @c std::runtime_error. Call member function @c what to get human
    /// readable message associated with the error.
    class ptree_error : public std::runtime_error
    {
    public:
        /// Instantiate a ptree_error instance with the given message.
        /// @param what The message to associate with this error.
        ptree_error(const std::string &what);

        ~ptree_error() throw();
    };


    /// Error indicating that translation from given value to the property tree
    /// data_type (or vice versa) failed. Derives from ptree_error.
    class ptree_bad_data : public ptree_error
    {
    public:
        /// Instantiate a ptree_bad_data instance with the given message and
        /// data.
        /// @param what The message to associate with this error.
        /// @param data The value associated with this error that was the source
        ///             of the translation failure.
        template<class T> ptree_bad_data(const std::string &what,
                                         const T &data);

        ~ptree_bad_data() throw();

        /// Retrieve the data associated with this error. This is the source
        /// value that failed to be translated. You need to explicitly
        /// specify its type.
        template<class T> T data() const;
    private:
        boost::any m_data;
    };


    /// Error indicating that specified path does not exist. Derives from
    /// ptree_error.
    class ptree_bad_path : public ptree_error
    {
    public:
        /// Instantiate a ptree_bad_path with the given message and path data.
        /// @param what The message to associate with this error.
        /// @param path The path that could not be found in the property_tree.
        template<class T> ptree_bad_path(const std::string &what,
                                         const T &path);

        ~ptree_bad_path() throw();

        /// Retrieve the invalid path. You need to explicitly specify the
        /// type of path.
        template<class T> T path() const;
    private:
        boost::any m_path;
    };

}}

#include <boost/property_tree/detail/exception_implementation.hpp>

#endif

/* exceptions.hpp
XQt83jm+1b84P/WgPKM7nHH/UQ3EufRozISXRafhMfa73Sr8dyk+Lc6XD1EPWyhP8f/NGsib43ylD73UdZ7P6z1HiId40PoivK2av92F583HvzrCxxPlWfeop50FX9nJiLnWvR1O+J7w7GPgm/hagi8WLoT/zZ1DWCd/pZfZZdGYnMSunsNfblAXuAofvigaW8PnpVfLP99hL+ruDTLS1dl8fg++2Jk/n4e35vBPvKTZ43gUXrq8K3/ooH9xj/g/xbxPSER6fxjOZODHaez4fH7cXV1MPS6/Bn97NcM8nTP5HT/qIi9sEo2Nb5EXsJtxJfLoK/FrvCirHrtVB8mdhLcV8NO+8jj5W1dxbF2lPKJMnvG4+lqVfvSJ6s70MeE5OKf/v/bohL6xPPMqerqQHft76pvs+1Lzdb0Fj8OJbdaZCz/y1En+Yf691HuvZ7euM2IffHgIDk7Ga/qLP3Bt4n/Fkbr4Yfw9qnz+PQ9vmqde95n5tLPut/HG3upp6jfN97g/vBmW4u/XwFV/JxvhlWXR+/NrwXt9vczR+P3F4t6f8TkecR4eJvfgvTn0fS584z95bfBxflT8NV73nzTnUONzwvBDPtW8F/+vz462629Wqm88zM9W8Cd2l5tP77XwiLj+eDxc8f9b+/Cjk/jFaOeWEtE46rD9qsEPStXVzhDXduKFPdX5esmfN7M3+Ntgi/k0cH2fX9+bf01hj23h0Fbxf5362Tnu/xY9Xim/flQeXZc/t1SHuFCcbaLOdIj9visv6YAPjInPMSbwFfpZ7fPny0PYaZk8qbiU35wGt07Wl746pY+Nb//ocy3Z/8Xykl/wupvYz1j9gxfw6mbq+XHd6Br2bB8avyZ/v0M8kLc0gHNLbxVP4Un3ZfjTErxrhnh/vTrBQ+77rPzgAvH6c7i5JH5eBHsYAe/3yGfmyjtHyh/Op4fd9DQQ391BD0PZyQ36hV9E/59ihytH4hENxPsUu5uoTvwxfeMZc+5Xb9vkeh+JS4t8/ivxK81+5+ExT8CVOu47l903xt/l58lG6Xi4+W/C896Dm/H3Xf8i3z/XvuJtJUvF5f7qU+ni5DzzPiUaJxwXjUX96Q3vbLgXv6+tLrtGH/PZuB6DRz8IDw6a73vwLwmvrsM7k/z1FP41WT5zOt6mPlR0VSp6/RN6FWcWfMgvWpvXrfLuXeo097DHV9lbwzg+wd2/u+8B+n0brzLvMadFY4MidUN5Zrvv8cejnSdoCldG4weJaOxdJyleR2OqU7rz/PTnXH4FXp6/PBp7G8vZR8mx7BxuDvtFPpVkJ94/7wn3GRTjXno0DscLergunlHvEn3Pb/GiN/Th2UnWh3Btm7xhO54/xzybqSvCkx0XOT9zGT7Y3/oug//8YWq563ZSL7hCPHpXnHqaHRwSf+hpWFZ6NN4ZjYO3sLP64mW1vHUJXOotX9+X4fN4Xex/V0ZjvvsWruGHzm+XpNvfT8yvPvxohhe2sM8r8aOv4XuJ8xCj7cOl6uWDzfcl9tLGurLxGOcJywaK98vE7zPZ9f36NDvkGaNc7zX8NiuhLoJPVMsHX6f3C+HAGvFIPlV8svcdhQ+oj7TuJq6eAYe3wu/75B36tNmnso/+eOT4ZPR5+VTFDvqAD0sv4f+NnFdRZ638jb9dAS83uo9zU1uv4Nf4WdMD6lafid//4hc99Ft22I8tiej/H9Cn/Ajf/podzbdP4lXjOeoAp7JH8bHqKfZ3LV4eP6/iaX70h3xEnyT5rrEc75nPj7e4jr5L7ln8aGY0FnzFD//Bb0Zbx+l4WQd+MVNcvA9fXeb6cV9fvTQn7pta9zznUGf+Jo5/xC8S/LIbP7fvo87Cl1w=
*/