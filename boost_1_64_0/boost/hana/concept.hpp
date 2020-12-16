/*!
@file
Master header for the `boost/hana/concept/` subdirectory.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_HPP
#define BOOST_HANA_CONCEPT_HPP

#include <boost/hana/concept/applicative.hpp>
#include <boost/hana/concept/comonad.hpp>
#include <boost/hana/concept/comparable.hpp>
#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/euclidean_ring.hpp>
#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/concept/functor.hpp>
#include <boost/hana/concept/group.hpp>
#include <boost/hana/concept/hashable.hpp>
#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/concept/iterable.hpp>
#include <boost/hana/concept/logical.hpp>
#include <boost/hana/concept/metafunction.hpp>
#include <boost/hana/concept/monad.hpp>
#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/concept/monoid.hpp>
#include <boost/hana/concept/orderable.hpp>
#include <boost/hana/concept/product.hpp>
#include <boost/hana/concept/ring.hpp>
#include <boost/hana/concept/searchable.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/concept/struct.hpp>

#endif // !BOOST_HANA_CONCEPT_HPP

/* concept.hpp
1Ofu90HvwJNPjGLssTWiPmeCe6/C1bHOJvX/ZmM/hTpWp3O5Ke287UfwzgPvKhcvVeDug2T8O3jjVZ6zEm6mNZVp+n7osKt12Gqwj9Ny/gfehp+5ec68zz6phX3fhmAnHsB5U4MqW+98QdTtQrAXKuVsO02isbSuuq15ELoOClPn+vAz4M0aVHm2+yJa1BDjJ/JZNgdrtR+5uBlu21bU5a3gndGn8iCpr4k5/iGMZf0uJo3WSW3MLjBbFriZsYKx687MTGn/PYwx5QOFmWjP5KkjTBj8elPS/w/uuovcXG69Zqn/Cd5rSpt1Ni+jN2LWaRP5bH4Ea/5Kn6BjfJH+L/C2Ufp7XXaJ9P/PRdkOqsx0rmDYRjU7V/r/wZ2h5NWZ1fOfEynyuvOj0DlQ81oRDjdS2Mjx+ZzJ7U8QY+lscI/149JCFoXSs8dYSP2rx3B2o5etYU1J6l+BmfAyNaztiDJe83HosHzmYdbWHeA4kYvse/YE+1KwTV923swVc/Ec874u0aZXeAKaSb7srDGV2S8nuJ3gnurH1VjPS8BN+nNjmVSaXXNbsKc+CQ0PXza9yBr2xEj9Q7Cv/VywD4gWDP69EII36Sn4zkd4WuPP3gCvW+HJqFvmPduiDYefxn4PoblT0XREXRVJssTMYvTYXAt3O5L6N+AOubmpApkz+VgLu79Fjn/PYH+Ph2udzVxsMw1u7QE5/oH7lotrSztk2/OE1uBbl+d/P4v9a2724RW1ES1r//L8B3AH/LlOdEU6HU0meN8nUeabP4c97KV8bTEIcvwHu0HMheyo52KstbxQ5J5/iXoe+zzirVUmnPA0NdHm+z8P3DM+UbmpopEhNYY8/9qm9H+BW9Pr4pYnouRBYGbK8e8F6D+4ylhGRGZpqsLuDxf5/QrsSld+E+UpDfkV73D6RexFdOX30EhVpHaifbKrpvORpf4P+D1+fA32u+A2v4S+w4+rwbbbFdwBcMcudHHrag+rpqMQJzRFyNA6MFrM6ThXTrSzyMtLOR8fVp8hckRDNb/Ok2C+AmZ4QQmz1WC23wVz71egVV7KpArmjR8Q/cdcMHfvUZnul4nbpyz1j17FXs6FXrZebfZbwf1qgYersT2Nfw26Jl6mhrqV/k8w3yplJlJJ3nX+PcWc/3WHuZarTtFNKAdvkyhegdYrCnHmOpbr/3iOeZ/7PQe/D036f9/A/r2eUi6EhVm54j3uBHdLH669IdoWpNCT51/Anr3Ahx3nt/NEnotvQpvB1dYaCBupqJxQbW3KZ7enpf8b7Ltcea6vPKi6KqJzjSrxFux4Vz1j96I1DlfWaeH2gjvtIx+uhvh7wY28jb2pPvnV4S+V+lfgnvyJH7dVW37D82AD+ORXh692T5FfcF9xtWeK/q9urJhQe2R1WLN9Lc8/fQcxNv1/8Rwa9O4F/w3wB0YrB012vsz/u/BDjcbXZO9vL+xe8H938avrDp1IDxCpDusYOwU7PB8aI6OwdcTmCPYzYD8xCltHny7Ye/dgjiVtFei5w9Gq88zK2WCvJNn69dy3eg/noKpMkoLTpX0n9a/BXWuEq11vb833ca6YwoQT3cUNUpCCFKQgBSlIQQrSfzONoWsUG5NsxrVgY6oWpo99yfQbQQpSkIIUpCAFKUhBClKQghSkIAVJTxpD1+qYux/eVB7dqdyetv/j9SWO35D63/h0x5dYo4pGD2+qOCBcW2gScQ4svCAFKUhBClKQghSkIAUpSEEKUpD+L2mU+X/puj1dmaP//tz/n3w/SEEKUpCCFKQgBSlIQQpSkIIUpCDpTWPoOgbz9+SezXREY8xMGYXm2mzRMDNGIhUrGs0d8WIuly40ZwodcbM=
*/