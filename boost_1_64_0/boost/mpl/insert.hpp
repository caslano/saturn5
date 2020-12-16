
#ifndef BOOST_MPL_INSERT_HPP_INCLUDED
#define BOOST_MPL_INSERT_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/insert_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/insert_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Pos_or_T)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct insert
    : insert_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,Pos_or_T,T >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,insert,(Sequence,Pos_or_T,T))
};

BOOST_MPL_AUX_NA_SPEC(3, insert)

}}

#endif // BOOST_MPL_INSERT_HPP_INCLUDED

/* insert.hpp
U3b690pBWhJpjNVVqvo2ryf9UCGYeUvK6WrDdGGqOV+NtRlHVrKtBhNWU7A4rFWDWjgDtdSEIy3lGUdWEg1iScIO6t4T/1N32Bvps+TxE4/8H5fHi9GXxXz/f8QB6cuDRenLgwekLw+WpC+jh0BfRvkM0aYvo6Qvo4X0hQUL6MuoTV++QaqCd/GQ9OkFve0tikGRxqR4Nz+q4xQDKesQswkpm/f60S63yCjvYQ34xaSoH66XLsNts9HLZtOvtHhrqoVABZ7dkI99Qz7o3JA3zn5mb0h7f/WGXPvrrENg4IuKbLDSAhVw5E9de2YkY4OuWR3ErFqMfQNRIjoIPHDqMrjxNHb5qkQpNmJjCEzNN++FvgeMXe8xSqj+SlXQ2uSwosXGM7yQA5bGrI037JNdgGfsoc0Pl3XtxNpKq83zZy9bKCjQPD+JL5YuaaDzMrG2mX9x7aWAbKDr8vmeSyoZ8HXsepd8UAw724OpNUDQU+co/Jzjd+LnmpL4yXo1qFehMLTCZtmsRwwtyZkL9w2Vq7UMiYWGOFU2tGKY01YN2cGXWlGdiazw+XM5RnKJL4kU3bktHsQt2aZSCTaVfp3DOpVJpFjqBpInwKbIE4/6Tvngs6hWqJwDAmCpVs9HP2rlNe1tNiIDivB2NxnpX5BCkmDqibDG65bUimreqHMLrz46p58M5vSThtLh3lcKLUmpiJbbfEKposM5hSP7K5xl0JxKRXNWVIYjK8ozjqxkm8/APIfz55m1fKhVDfrmA/5UZxxZSTSImQ47t230T93+ykjfeRap2jfrmU2qDsvHpnc3Vz5WeeKQyd2DJcnd6CGQO3D3UQe5GyW5Gy0kdyxYQO5GbXJXfXjIHYCQZjY/DPFDiys5HZYiR6P2la4SV0QQGfFzHEFKKUHurlFq/ML1AjnEFQALIYhTa/7cT3HlWfrwhNCHB0kfLPLwi8r/RfIg/m8My7/O3JupM1ZuSqCY6to7QxiT6dtt4iQA/dzmPWVVuwvUs9uXzWc42GWyFTjNuCZYfgLfT4STzScd1F5TxT+Fla9u2tqqPH5MbpylvN2cEjNWc4NKlGTcQL4RWwLKUktnRu2av5JphlMx6K/hLgxYbVcqsK0SVTzThHGmSc/VkoWYq/oNjqjRAGjWqaPOIk9B6Sjoc3VUXaSjWa6OQnZH+fruvT92T6geLsmC1hLTErf9szM9hzXW3gHX42Z/wXpszpapJcGG2L3H8je2xceH3cbS6ORqsRiYi0xNR2iLcs9npn0Z7bwvONrPeMOB3L0LqVJAOeJSscpINbIkaUFlxwZFZlm/QMacHnhHQ97k5jHLqhrLAyUMg3oFaRpzJ2O0fXs6kOXB11FmwVcaMFzqRKd6YlNrN3u7Y1MapCkeA6dwie1LVzB8XT+7P4j/vGr0d+ab0KMm71kh73ypRVvanyOZ/tDKqCpeYjCOFSncPx/ZOEOQSqmO79+74K9tEjFyrTQ0w/Knp5e6Jz7R3VKNm5qF4E3z7YDgMOGM7QcbgOXnw4yeOI8uyqCfh6Jgnrd0X/+8b8FvdNuhu9qq93c+JP06K6R23r+/6vca9mD3PGPsGLlhfev0V2Ua+Pxz71+mSsRPN1afmIovXMkg6JZVT2uAZ3hGiqbzqwk/R53+aeqPB6VnJzD+IfuzwpDOSwV46zUfXHrI67idb8EXouM51M6/iWsXwKwrvI7AC0+Gt9rZnnimW2wnemKZbmWM4AUq51zQad9SCjEwuQYnVyJof473pRcra6U6jnEqvhB7UsX622JFKzdW19PIIMsxZ1NGBF6txnXSeFJ65QPP8aQvvS13Z6p1m/alpEbSbo7pPHWrWce+Vb+oC3nRcT0=
*/