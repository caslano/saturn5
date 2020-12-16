/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_PREDICATES_SUB_SUPER_SET_HPP_JOFA_101102
#define BOOST_ICL_PREDICATES_SUB_SUPER_SET_HPP_JOFA_101102

#include <boost/icl/type_traits/predicate.hpp>
#include <boost/icl/type_traits/type_to_string.hpp>

namespace boost{namespace icl
{

    /// Functor class template contained_in implements the subset relation.
    template<class Type> 
    struct sub_super_set : public relation<Type,Type>
    {
        /// Apply the subset relation.
        /** <tt>contained_in(sub, super)</tt> is true if <tt>sub</tt> 
            is contained in <tt>super</tt> */
        bool operator()(const Type& sub, const Type& super)const
        {
            return contains(super, sub);
        }
    };

    template<>
    inline std::string unary_template_to_string<icl::sub_super_set>::apply()  
    { return "C="; }

    /// Functor class template <b>contains</b> implements the superset relation. 
    template<class Type> 
    struct super_sub_set : public relation<Type,Type>
    {
        /// Apply the superset relation.
        /** <tt>contains(super, sub)</tt> is true if <tt>super</tt> containes 
            <tt>sub</tt> */
        bool operator()(const Type& super, const Type& sub)const
        {
            return contains(super, sub);
        }
    };

    template<>
    inline std::string unary_template_to_string<icl::super_sub_set>::apply()  
    { return "D="; }

}} // namespace icl boost

#endif


/* sub_super_set.hpp
eskFRfVC7PKjeimtWWjeUxg4JCODVGnHx5X/9vrtLDLuGkXGjW3JOGIYGZ2tsBWwbU8qO/83f5X7AoHfd1S3TpJ+cN9nNtltOZXGQRUAFg2THHYTDrWXhyLIbwJL3XKw32dUf0ba/+3jzBfDjQuBqdvDjYR0aauynbpN2R5h/BU7qv6WcUDaFG4Ungs3Gp9X2QX97WN3ueOh6v4Cn/UYXxqykOki5cuZhBTwxU0+7jnWmmtyWP00/3CnyYHrQ7X9w+1pkN/zRlEuiDpZgrHxmplRcDZSzxusTaEnV+1bX/54ILTzd2Ptu2llBc5AqVaeX5zjsUFSPT/GIrDMcZ6SswbGCIPSU7sJrb2EJM98yJ9mlTg1SUp95H5f+pirnyd/J1bDy3TZi5VnvW4KLU2gYDe5myAIkg3bDpJO027YQ0phzYORlCXi3CYiA/sWSaN7yFhbIGPPHmR8ZRAZD7Ui491mMq5MVr7D/ll3Mi6JJ2OXwWQ8Ab2D2L8lD7yuZNzblIyjksh4rH5gX7YT8m+ArzuT8aa2ZPyiNRkH5JNx12CUExWoO645Ge3NFd4KlP0S0Bh5/lu/w66M3/kPnCo+kUPI+MAtZGxtIeO3w8i4LO/fG5/YSDK+zOz/Y9+pl8fAguwv3KqOu4q4RiCuYwf9e+NaK5OMz2b+x+Na7vv/w2MTEmK6+u8HFFow2/Nc8pwlsVQzTIacSs9EGvcDpZERxoWNI4xCgwhjdKMI42hshVsjjIR9d8MI41RgIUCadEnFW4H90Y38tKq8SpP7tohqx0UvLYS9u3HweVQZ4yJTuWtx6w7eHukDhyZnpKcK7APTAm66etX0y1nY2bNgFJ7IutUsbzukd0Z6CjfV2irPcoppNXx15uHxXdqYLM7cAHdJkZnkuSavK9dnsrvM0r61GHcINukGwpdPflrp5weZMpOz+yl9CBFl4LpjSk5NJWl/ULK8TRuQmT2CiKQHbtlezDVLs3RljY09EXSUn1Z6yvte6ZHe5ezp98sbVN18nsD2nqr4LCg6AmomPRHwpx0qS/uJKPzzSKPvi0hjCPs2zVbslwIGIjpARDd9GWk0fqnI3yaihtBP+lKRHySi5dhfx+hDRBR+NtJY/6yif5iIWkE/E3QYBZey3KLFlmvD46MvXxSko4GHOGlffthLG9g3fWCaoMxtC7jr9pg9xaROAweZhqb0S0vpH5iXS7DgqmRzFoiCWIinD1uugEd3+WlLHvtDnOSbda/QLsflsotmZ3sKSOmp6vzMTu6KzcoeP10eHnDiaVi+CMc9UukY9RPMsoJoZaa8XjYnniidZjuq4/UJ7aJ7Ol0dY3oWi96OsT0dZqdVunkqbk+alJo+2MTansqv8WUlymUJ0sCx0Ba6UnNtiwdHjOogO6hWuyBWFmvulGy1ovplORUrRYzPt1nyWb28ggXhyRFZbcmfMiSXCtxyrfmRZK5bped4l+w7Bq98iKK3mv2S/3ywFmvuFwtVExs5mNI2KcqkOr/5mAynlakIjNZDUEREal3WVfhpr46uUi82yuunc4rR5ahoi8MqjYaKRaKlQP6Vmcaeu6WmJSM9njSExJsdl0kDf978MlqZfbG589mTfgCfDydo+bk2D9iBPLsZLA3PKRaV40lDUvIEv3zFINKVc5FW5hEL1TzepfK+WzpPWIADeR7R4SoU1fnJh0we9GNzFFqZasKgvJ3Xi/jabaITsWPj3GoddEhqWlVnRF8+KgH63D1Oy82HXybUh1Att1kDaT7JxOsttx3knIf682PLZQVOuwvjL1beGNR5F7hhlEtE6H2UhpQv2t1SDozH8kCvmWvLYyNdGhkekgvsov/wkNnuEc3W4oA=
*/