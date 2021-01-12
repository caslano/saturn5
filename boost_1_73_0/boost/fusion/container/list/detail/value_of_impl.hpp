/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_OF_IMPL_07172005_0838)
#define FUSION_VALUE_OF_IMPL_07172005_0838

namespace boost { namespace fusion
{
    struct cons_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<cons_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::cons_type cons_type;
                typedef typename cons_type::car_type type;
            };
        };
    }

}}

#endif



/* value_of_impl.hpp
YnQB+uoU+43AStuT1d7/Ly4t5aG8rKaV1v+/C0vz9Tlxgbvi+n9bZ3Ftz/Kt/4flcRPYLWubTM6QZ8XiCvY4wWvCkYd+89f4DvH5Y54vT5f9G/Nb146wxjiR8MyY4/MLeJnEW0u3Xedi2Q6ZtZFOSW95Hbz4ekjeMXLiduv3+vyEZ+avyHQN+Dnc0ZunOquJL4R4VRSGZzq+NQojNaVh8QkYWBfkkbimYTi6v8QPXgPGV3fd
*/