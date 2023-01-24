//
//  Copyright (c) 2000-2002
//  Joerg Walter, Mathias Koch
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  The authors gratefully acknowledge the support of
//  GeNeSys mbH & Co. KG in producing this work.
//

#ifndef _BOOST_UBLAS_TEMPORARY_
#define _BOOST_UBLAS_TEMPORARY_


namespace boost { namespace numeric { namespace ublas {

/// For the creation of temporary vectors in the assignment of proxies
template <class M>
struct vector_temporary_traits {
   typedef typename M::vector_temporary_type type ;
};

/// For the creation of temporary vectors in the assignment of proxies
template <class M>
struct matrix_temporary_traits {
   typedef typename M::matrix_temporary_type type ;
};

} } }

#endif

/* temporary.hpp
eDYOuz4/sAvypm3sIdE3cvVOwJ9aHeGCOyVwi0iBChppF5h8+iydhzNpkikw94NwntldO47dHpH5TlZfvicd7fLV/G1viz5m9Lbazyf+EucRqLVLx5tCEQI5xDrt6DlFXRt3GKj8V2wMa2ZgJO+N5+sn/Otf85rfv2szx5bR7RopuiHOtVjHs1K29LH/fSk6cL5TP+eEjexGoPjg9EFGvIazMfU6V8GkQkXiByHTQlVOlcUMqW9vQQW+7Sci2pREGkUhmqoNOf0XOZimcgTMJwa5k7ZoUosdAluozVSr9L2eDst+RYU//ZwGxfjBhb9G364ibO4omZiFxOZcEwfzzxlG8VpacV4pS7oeZR97JUtV3JHFoiVyQLHwXagKMnR98VpVXcn6kzvi/v3KdlWeTNDpImbHR8Gf0N/l3plKyYHmeoXbn8k584ZfznMO+ZuVXlxWom2ylHjfJY0WaQrrqxqmgu7PjbhaHc9rGHItcHjOqW1W8qSO7CKhEfo5i6SAQG0HBqjtnxqdTC5Lkpym1GRJlJwmB3s96Yqr4iYblz6pf3ZLNDD7mIzF4LKS1PvWOJUrHOWozMutP3UhVmoyj69TFMwNFop/jry38TTMkDFDehkNRrdGZOhfRhmf3wQpuE93stXpdtdnEE9dSBm+0z6g7NQ652XvIsftc4ydeswmP/Htm+ORlr9tFHaGOkN7O0v+qj0CP3p7r/+z
*/