/*!
@file
Defines `boost::hana::reverse_fold`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_REVERSE_FOLD_HPP
#define BOOST_HANA_REVERSE_FOLD_HPP

#include <boost/hana/fwd/reverse_fold.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/fold_right.hpp>
#include <boost/hana/functional/flip.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename S, typename F>
    constexpr decltype(auto) reverse_fold_t::operator()(Xs&& xs, S&& s, F&& f) const {
        return hana::fold_right(static_cast<Xs&&>(xs),
                                static_cast<S&&>(s),
                                hana::flip(static_cast<F&&>(f)));
    }

    template <typename Xs, typename F>
    constexpr decltype(auto) reverse_fold_t::operator()(Xs&& xs, F&& f) const {
        return hana::fold_right(static_cast<Xs&&>(xs),
                                hana::flip(static_cast<F&&>(f)));
    }
    //! @endcond
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_REVERSE_FOLD_HPP

/* reverse_fold.hpp
SntMgizSyhqislHiu6f9mtI61jdGSFtWg4BRd+HqV3cDxlZ6N09n2U4+Jp2uOK8ULRoK9Kld57PxFka6SknF4twKtAXGb8to4UPbumuVHxcMmoS0T8naIfy7kJAV26fEeG/Nv430ITQb77OQ8DfJHH4epeWa9XUrvDX5f8StP37fYdUMaZ4nRxv5j4x8YCrJq7oKZ5HuvVn0WkKAiIbSiLm0upjOgXzcS971bXR+HkucIX7K8w6BLBRwlld3H/KIaUyVz6U0738Z074U0rYDTOTa+vlAu3NZqDPRAk1KuxDS/C1xmvbTkLa2D/tn4PkiaPFvQlpc5758TP9zqmsypL3thpAZYkuA/hd4+vJvh7TDzKcN02QS/dre4d96vCwVYxQY5+PhD3nv9G84mNfZZRnygo/pNaD8NujJVobJsQJ9Duk3T+n7mIFvGve4DPALYwL9J+8Wz8T0QQwNupmUd9mUF8YHy/wQ00N/ot1i1M9cHvPonQzLfu4KKR+uen6ISH23vWLKO7u+uTNNv/9VU3oe6+SNV5um7xE+7zuU0sN1EdNffo2Ufm6N9vN510zpW+B9OW3rt66b0uFYWtkF4ZqMzfVS3s7qBunflW+A6dC5cI3FMu5GKS/n9XJMD9sb8nr1TTAd513MAxC8mIdQrlOMPHZLnwdHijdYWAw2B9PY99bfiRG8G/0l8a59P59/ejVmrKS79G9eFtLDHJkMmVupjHtVyDsX01cx/VMhfXczpqPP61di+mLus5nKXfz14BP7kMnekIU2tT8O6WdDj0ZteOOvQ94kNhz17Bd+F9NJoVTmc3/xeeunYwPOod3xP4d0UgTL7FzJ6xzAtnNUz6EbD+kAGoyDirjAt/N5sBBAwZXykN9qyDu/Meqru4NPB4dTaPqY34U7xTyErprmseMxbzeWo+Ma6vJrKx+HQ6d9+iZECs3TX3p3n741SUF+sM0q6F1OTyIfxEeGv5fCuUUw79O5cQnIh7lF/W1S2ZdeFvJwfiEBln3m5UL+OZK3hfrHq0Oen08kL/F114I8MtfGbTp0bcgPcw2zsE0XXxfycL7Ntunw9UM+DPRsvZ+7QcwbFcZYOR77E+YYYbuNY3GTIe+get1hyA9zcLbe39wc8uI8JEXxG7FbQn6ci5hPx9mfZ2E+Yu4E2+XLxjlJy+J43SrmU7g1kv++W0N+nJvz6j5yBPKH+Yl143j5vDBHZ/PeeBvIC/N0Nu/IbSFvmKuYl+TWx9b03ipAsi+amoO/28gX77YvyHDT6kpzqx2LkzWXha/8DioLGyEUCK6awcQd6d0zugo0F7ZoDIOJOsKRonR3k21r2royDCd0bOolUFdJ6Y9aW7d1xy3zExxthBPvhSfRtwdbgAynip6lSTvz9nAPynux5mUtOVs/PRNzh1G6i6TT2r9TACVhm3i+60WZjs7H22majsHkzmXeOnurkU1jtUcwGCby6Hu5bAy6ti+FdCXzk3rmnnH/jG/XtZ1tGsmGST7i++CsX7ape2cVi/N9RHs242ua3tqyrz3x7gzf81l7S1v12nUF8xN6pr0XZ7Q1b2Xpqo75CT5D+5SsDX2rZdVIy4bHs1Ebnkdpj0nZW2HKktE5hrQvzWg7Ib0q0QbapTHtq7P2NqC6VEIZNh0x8n73xmyuc+5K0zQNQ0DZ8Vx/X/Y9etVURdnVLAIH5/PnY1mbe91WjeMto0GqkPZz2bg1RVlZySsWQ8nl43Yho3VVD4ui0Qw+MjYBaX9KaZd0XXHZwhPiSvTMzdb9nzNaWcMMdlwC8WR9F/0vyVhc+p25/l7wqik40O9hB1miPURpL/IATbV/vp/AE8nKxlo+boezd8+64V1Vtoo=
*/