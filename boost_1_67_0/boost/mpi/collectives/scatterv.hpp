// Copyright (C) 2011 Júlio Hoffimann.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Message Passing Interface 1.1 -- Section 4.6. Scatterv
#ifndef BOOST_MPI_SCATTERV_HPP
#define BOOST_MPI_SCATTERV_HPP

#include <boost/scoped_array.hpp>
#include <boost/mpi/collectives/scatter.hpp>
#include <boost/mpi/detail/offsets.hpp>
#include <boost/mpi/detail/antiques.hpp>

namespace boost { namespace mpi {

namespace detail {

//////////////////////////////////////////////
/// Implementation for MPI primitive types ///
//////////////////////////////////////////////

// We're scattering from the root for a type that has an associated MPI
// datatype, so we'll use MPI_Scatterv to do all of the work.
template<typename T>
void
scatterv_impl(const communicator& comm, const T* in_values, T* out_values, int out_size,
              const int* sizes, const int* displs, int root, mpl::true_)
{
  assert(!sizes || out_size == sizes[comm.rank()]);
  assert(bool(sizes) == bool(in_values));
  
  scoped_array<int> new_offsets_mem(make_offsets(comm, sizes, displs, root));
  if (new_offsets_mem) displs = new_offsets_mem.get();
  MPI_Datatype type = get_mpi_datatype<T>(*in_values);
  BOOST_MPI_CHECK_RESULT(MPI_Scatterv,
                         (const_cast<T*>(in_values), const_cast<int*>(sizes),
                          const_cast<int*>(displs), type,
                          out_values, out_size, type, root, comm));
}

// We're scattering from a non-root for a type that has an associated MPI
// datatype, so we'll use MPI_Scatterv to do all of the work.
template<typename T>
void
scatterv_impl(const communicator& comm, T* out_values, int out_size, int root, 
              mpl::true_ is_mpi_type)
{
  scatterv_impl(comm, (T const*)0, out_values, out_size, 
                (const int*)0, (const int*)0, root, is_mpi_type);
}

//////////////////////////////////////////////////
/// Implementation for non MPI primitive types ///
//////////////////////////////////////////////////

// We're scattering from the root for a type that does not have an
// associated MPI datatype, so we'll need to serialize it.
template<typename T>
void
scatterv_impl(const communicator& comm, const T* in_values, T* out_values, int out_size,
              int const* sizes, int const* displs, int root, mpl::false_)
{
  packed_oarchive::buffer_type sendbuf;
  bool is_root = comm.rank() == root;
  int nproc = comm.size();
  std::vector<int> archsizes;
  if (is_root) {
    assert(out_size == sizes[comm.rank()]);
    archsizes.resize(nproc);
    std::vector<int> skipped;
    if (displs) {
      skipped.resize(nproc);
      offsets2skipped(sizes, displs, c_data(skipped), nproc);
      displs = c_data(skipped);
    }
    fill_scatter_sendbuf(comm, in_values, sizes, (int const*)0, sendbuf, archsizes);
  }
  dispatch_scatter_sendbuf(comm, sendbuf, archsizes, (T const*)0, out_values, out_size, root);
}

// We're scattering to a non-root for a type that does not have an
// associated MPI datatype. input data not needed.
// it.
template<typename T>
void
scatterv_impl(const communicator& comm, T* out_values, int n, int root, 
              mpl::false_ isnt_mpi_type)
{
  assert(root != comm.rank());
  scatterv_impl(comm, (T const*)0, out_values, n, (int const*)0, (int const*)0, root, isnt_mpi_type);
}

} // end namespace detail

template<typename T>
void
scatterv(const communicator& comm, const T* in_values,
         const std::vector<int>& sizes, const std::vector<int>& displs,
         T* out_values, int out_size, int root)
{
  using detail::c_data;
  detail::scatterv_impl(comm, in_values, out_values, out_size, c_data(sizes), c_data(displs), 
                root, is_mpi_datatype<T>());
}

template<typename T>
void
scatterv(const communicator& comm, const std::vector<T>& in_values, 
         const std::vector<int>& sizes, const std::vector<int>& displs,
         T* out_values, int out_size, int root)
{
  using detail::c_data;
  ::boost::mpi::scatterv(comm, c_data(in_values), sizes, displs,
                         out_values, out_size, root);
}

template<typename T>
void scatterv(const communicator& comm, T* out_values, int out_size, int root)
{
  BOOST_ASSERT(comm.rank() != root);
  detail::scatterv_impl(comm, out_values, out_size, root, is_mpi_datatype<T>());
}

///////////////////////
// common use versions
///////////////////////
template<typename T>
void
scatterv(const communicator& comm, const T* in_values,
         const std::vector<int>& sizes, T* out_values, int root)
{
  using detail::c_data;
  detail::scatterv_impl(comm, in_values, out_values, sizes[comm.rank()], 
                        c_data(sizes), (int const*)0,
                        root, is_mpi_datatype<T>());
}

template<typename T>
void
scatterv(const communicator& comm, const std::vector<T>& in_values,
         const std::vector<int>& sizes, T* out_values, int root)
{
  ::boost::mpi::scatterv(comm, &in_values[0], sizes, out_values, root);
}

template<typename T>
void
scatterv(const communicator& comm, const T* in_values,
         T* out_values, int n, int root)
{
  detail::scatterv_impl(comm, in_values, out_values, n, (int const*)0, (int const*)0,
                root, is_mpi_datatype<T>());
}

template<typename T>
void
scatterv(const communicator& comm, const std::vector<T>& in_values,
         T* out_values, int out_size, int root)
{
  ::boost::mpi::scatterv(comm, &in_values[0], out_values, out_size, root);
}

} } // end namespace boost::mpi

#endif // BOOST_MPI_SCATTERV_HPP

/* scatterv.hpp
H/1xtrfDWvxmKRgV/PcVxO5uiDTZPQgzau6CnBe5P/YXH2LCivRu2JKbSsaQbsQBICNlpFt1gcLlsfhn9Sk8kEGYuC3VzU6MC7bw3fXzGhozKiOcwONty3qu/zL8HX+jRMPp6i5A77oBF6SdK00DWY2pl0ldqZfNbgJV1ItVxYGxf5p8BEnQyC83aC2h2LdLB5YynqHx7DKF5/yVBk36HViOBQAeqIABLjM4YEZc2Q+uGmSwGXTApHE1Unl0DfJNflJS1QkNMrxrr5FTfNruDRqbtcGFbAgGqVwrli68qIbweQCvJldWhuCAfjTi/TLSW2n4Xs7vTxOMxX9OKUnaJQ6ahf3PPNpAByLhCmQbCgiP9hQ3uY/vd3Zf895cjy0h6KVaUiym8mPlcY88sAWx6NpfiexT+MCUOpgQXhQzS9593MehXBxpOxNnLuv9nbj3+nm8c9qc+xLm5FJMsWPwyA9tJTmPT6R6wLZFa502Rc1H4ttdTznnxShP7Bc4Sjz/sEYWGSxYgEIPd62IUbTTtmZR8juefN7khjrD8khUCx6IGY3ZVIxqFawubK25w7ALq3Ufo2DyUYNyKDl/8rwQ3UrIaCaBoWSyI7UV5kOzesJ8jX49m9JCPZu/57Fu1h0z9RpyHqGze5jsOJKK8gX2QMJAYceuqTQM9+wkNqW3CJvgZaNUdlDCOdN8YgPiSoJSy7Do56qbHsqlAPwsnPtu5hrn+e3WbBU5DXQiTmySOiRG4k8rPl6aNeckwPFZ9XDvBct5KXNdKcEJfrtk/W0a6tExzpiDC0F1z25sFOtgbtwWfVjZY82nuvrLUosUwYPFSu3MCFANiXjIhGgiYPfPlYfmX7gge4QfAiJDtrJqnTvVXO8iBb7HewkLIU/qDRBes9Mn//IdvDRqY2jYsZgUYTC9xFYbmsuvxDuQ+hQAJpyszgcN6/LgHH1fM+vmxwXTmctPk1Q/wnHjpRXiTb3nHwHYECDXTZSuNyKmUMFYEvHIGpK1278OOJvytSmjVJIdR1G702+X8+0ZAY69YMcsXQp/AkHIt0bmViwjgvdc1MWOT5syZOX93SKttfhjdSFEvZD/yyBMrx7CHhqffNFCXM/Gtfp8xK65FqmVIP5y+S4PtBOgtI2WbrnNfiReSD78zy945+dbNlVaqKWFrerdoFWn65RK4w4HhOj3/Q6uhHPeKw1PbUs9GTmqqI0yGMwFCOX5GdtxS2ZFeBE4q9Pm9uKZVfYxZvJ9Ue7WfdtU3RFtB47S9bjZpTl3oO1KuwXrelQH1EZvGLFW/4a1bO3Hj0JdgeKzbW5dbTsbhluCvaoxjOIzH7rlv5WsXMRmBASMxnq7TezuyH67rBv+0B1oVdLQh/l2eZGdEdD5nYu9JmtU9a/ETFZHHALizOlfvnru4M0si+t4bcAtsuyntNBEDmloKW+W5zlAbOkEH14Ry9ye+qg6y/6X3wxaCgEOqril+Ot/Xjfowle57Cuk4Sw9LQpLrv2TIOdSCSynwqJeAxxHsitqlfnrNfhPCSLoswba+XPyunfF6FlNRbnzNd76/Jzq5OeGa6C5smWvnFVvx99XrB+BUwI9fqT+2Ca3IwZugOXHWmjt5ok0okOgVbH5Y6wT6aAX3QGBaeM0oo0wdl3ptlz2O/pFb5Mn0UKa7BJanwfxIIdTlodo2Kusra3K5Shd+bqf/xy1ufoEgZHl2f/JSgPLZooWbou0UzElb7J3JR9sL76TA8nnY4ftePZt7Mq+dX5WFu/XnnWFymZ+0SeGvxVvNavpxfiRI68gTJe2DxU0ap7nfbUfLW38cjn6UV2B0X6U210A2diSGmBXPsj2TUAW9wKxGxLfkpoDMBW4gsh0qn6Mkp+Qieasis8B0ElVejpgOEdkjmonqywhgDuSHSCHz44jVcD+RB7QSl3J/gKO2ofL1FNbenNn4QhYUZonlPfNwOVDPfeVFvsDjqmtxDs+Arx4wYIkMpEmrVMrEbDHHTyA+Y7PWI+3lK44o2eNAgH+pEsE6HtLRFf3iUKCzIORswJLM9Ahd5/8+waNRq7GtFIOHaNnMR26guT2EW3kXponQ9IkxnkWXll3WdhDJcTi+k+NB2l7pN+MIelaj4cQSXuzXzNO/0UlPKOyzefIBuENyBtPXudS6Hfm15s6X405ZAyC4COgk0jl0LygXY6PQFifv0uJP+X81pX85yhy/zIKZvhHVgnoYesUfHhxvJs+lQc8rj4Cb08iylN0CQX5U2bh1MNl7uXgLGSclFQ70k5xJPVcXBVCtLckyXcMTJNrVe/WBSIvIdas8bUs7tsTkEnx8NlpmrFAMfomVUEK5I07XVY/xe6Z2sFh/rJngWx2cH5ENi4ysyBWCorN9QukRj6+Xb+ZhraJK7wOVOqo2elWyLdc9B5uL45FfxD0d1njYBZQquYGTHsBucl8pMrcwc5Np8eISed/8BCQPUmQ1oF86gL0khKjGITCR3iqbFNKKkhNVQf+cTyOpVxsZmdFVAt57WC6EWyb6vQBrgxAzN9rV4SMhZzYZoYP/qSKxEeQwWwwVBPPyTnfb/qeg1O+5/JsDz3Td5OFjVfH9ZJMMmfIaUHEZiSlzWZ/2vmWiAOl5EcNEueBldpEu6TuRAfIDrQ47pn+xju/fZWTGvE/Eow0Aa6vIT6cq7iXxJ4/LvQzdxtGc/DMPKn3lFffIA2m3yDfOf9uvXRh7fu4FqGRAhQxf0udaxRc2vDzFPcQ+zxq4cFxxA0e1BAB+d8TtXBApurDwuAv+RRlRPv3yIHTmLfELpy1JAaka0QBZAiacxxTR/sS1ziPnDn9uycvhI8+iEkkksYOfd59fdWHp2yOlnK1ZM6qbG5aXWlCNWNP7FFVVUMPQ94wvTV+tNPX+rJ3QCXuxfuJx9MJBDtime+eyRALhyravuSy7HBd9R3ztzOn7JBGLkCkIRh5MMq/m2Z3vMHtzAhMJPPMdIJKDrTIcfFVE8/7D75lMsWVcM0X3NqrIXoSI9Xa1L4vD2RPBn2/jph1fVtzi3UxEfqDkHywml87zzyabmKx/sDo85JXaM7nJcwDox2d4zxmJNM7T1bfYZQLjqqeyk3Iit5KsQgfyWRF5TZXuo/zJC21n1Rk4zz0mwCKtijYZukHzEBqkANEE5ttK0JuBLvrQRc/KTd9m8An5XMOT0+pJVhBS2tErM7Iwf0fZuhj1aAJ9eC8m6xO/x/k+vfgHPjpRgQfOuKdt1ED4Aa5VyB8DApvRPme78MnlPd3OfJXcKJFp11FK4q9fjTNOeYCEetatf0kKOJeTZ6TZ716BPNI8N8BCIGwN9lvirAfNQyfL6Z+xHfWQx45CP9QIPS3VBLHca49npEhYFWXmUcD9xp04nAtCeKsEeuatQQRTcRelTozGM/SLziO7EzBPRzxQmHtvJGa7Olr8NEnGKCPN9T9iyteuM4nW6anBvotvbnrfv47jotnNDkdqc2Zbfa6XbEN9keqTm0LszpaY9VGY1v3drPWZ2w2QuT+xS1Z8ClG/Zz8k9COU6p1isAkm3dxdKKeVCUcijattgKbW6jY6frYvN7dwsoTUnozEhAHzq+3CwEkGd6Lvr8buGJ9PzDY+PdLrTIPLW+8nLyJjNNc9NouzIc98egmz+GcRnJ4BLENtbOci1p4YpOXXOA9aTdlGKG+i5uya61QgVc47WKcyFZsiGi1VJPsuzwCiB8wZf73D1vRVeJF1sRLI3qqs9sfKe6BA51aN9DWOBh4IJ62t+vlki+BF8U20uXNEcykyAbvEm/3+S/uRc3cXLTmzLfCVnuWt5XxZUXDtG8//ObZZtjxJvWRja4jP1f9zYflrZMmNNnRvrsblz9+rtVt9PaHXXxYcEORk78uWjH0+jWgbLGo6pVU/3ucYWjOK4Xqm/dITOGl9ldk7bSWwFpIc9GJfCovSpXpHSqMYlUE2fCw9Hs5TOiBLDEGwIOhDt850oHiICPGdZQoucAjjJaUb7Hiq9pBhRNaHgxBHy+Hhk60e6qLMabP96GbBsiWSCf8mKCUud7MdfHsqSNtNhyli6GefCYF4p8k7nMdrF2kTvbq5uJyvB5NX8FxylTeHf1zd0lvNIfmsOxbxvg2j207H+ugAOHH8ZZa3PFwFRbh+ztcgMI3UQSsXsY5AK7sp1I7CeBBXfSUSlBJ1/Q7tANekERIw2Pi0cUu4pO/zx6NP+c4tgJyuxDe7zwLb8epOtA+PkIz98bznhxxzbDTNieam6hdKY+UPll8No/x/t1Pqqn/6RrH1S3pD3aaKUleAr7/GpuZ0o7g4/W8wD/RI3/otBx8t1Tb1zflhJ+0S5KVwdjD7cnLkIrjYX2agsEmxtbdvgoA5zbfXZWsOMnxNRtf2F/knvPturvN7RB2c00SwzbojnSePYGhZRl8QcGdaadmTAluXSTImtuuzlTJfx9WkslBNjuCzeQgc069sjiDAomvESs/aO2yDN7ZG/2gDI7TXpLCZwb3DQnVXtA7TPQMsfKuAd5nyPwUMrcfxR3tDtPpcKsbFWtGGjmZcLv7G+fJfz/aRZ/AZiv4jos8f839/NXXKhXh6nr0cbCFlLLomZZzGW4KRfCLXov/gnQE5/F+HfeUxZspSMFRqj98R6MCplgVENttR3mR/K7/IxNY4b0lgEfgGiOcq1X6N0Mq6+CFEoTMylNlzNOaEHZvJDIWvUFyOF4GBdR62HyQNn62JBxhstJ8zvS+zdHkUEsfEYfEYCVmVXIkbAs9HSXB3AIcWouiv4LM6zj32skuBSEfB+Gy4wAELPvTN/tg12kTzdnbN9b+OLebtuzcvdMldtBbPzmKs+PeDcHSesoT10cVs+Un+ATn8dJjuJZk34dS9LTDXNmZSrS4cHP5sN+goI+DgKcspCz+jy6ICDWMjLB4Fz834/n8jR6WPpgUOxGY/HPBvtXeYIcJM+8yHFga+XNN2ccb7P7Z1Q5+CdtfMJ2Zyocb09k8aZhJFbShAvHwOzpoa26w8rtfnrUqcvvLUEJ2yXbbs0+anCdHTf2pczE9Eb0xSlpcUQ2J0tcYoaQFYpegSDT5JTQ7GjCrtDHsO6AymuV25fXCON4djGB67sd8mR617zrML7THMKYuPXT5KZ5ityKhRplCiS0K/URoD8GbCwqWk+TXRxNFnhCayLL97z8zAj3m5jOGC9X527PPGou7t3Md1OQdiiVK7QX8V9ZzmnOr7NflD+2M7KQl8g0eOKi+iQtND7/H8czqMZcVHgcZR0j4uYiv0uN35sE/7j9mfBneyYsf+oZY5PVAq9uKtY8Cwr8sMwoNkwdNwLyg7mCoOzQuDvaPPq3kBpB0epmQ6ZCyIzYUYpuN0Uz2kEviOkxP4fKSS+YKCiAwTuAKErynX/QTV9GzIvbz53oGF2qVqIfT1g27acV0sXt4hIX+VMktTYaYu7XrmA0zdZoW20QrMX9qVAiTyNRkTqreBpHlDrTxYe1/y2u1ApL+dU9Yn4nrB0hZViNc6KS8BVED5hhjcaywlWpK1f2whV8FZyDh7+vRXtP51zwr4cNxyMjfGn5rbP4EZL5bZNsNos+cORnXFH9xXO98jZwDZu1LW9bcVy7xZ7N5BHGNdGOz4YFcROYk7QX1vROq50vUJZK4xH2zMukeX02glcxrdTvfRw78mqLvGApV3Ibn/YXEJyHtMLPTVJ8btcO87iGhYYlIzUB28eXvcPoymGJyVK43heUHb2R82uikT7W8F9tes2FeHOTrTgdQKNCMV7Yr2VouTRgZM+yuRsogK9TqFyDtGrK7o3OEW8TEsV5oVXfbOaHQrA3Vmav7a1tLFwPJE8A8dFLrAoH+8Bs9wUcgvbC4I/i4IxM47ytYXzQnAC5v2+iYMZEmYqj/sdMiTJJ2I+J8n3+DCiC24uBjtBmoc6FwrtoRV/Vyd1jACmzBcfyV9Dn07J4qzH/mtSd2NiHjz3ehL4c6jZYlS8cBvDqxQaT+RGpaxqlFO/abfw1nqp8HWzZky497KXu50dks1Es1RE6QvczDCY1vf1BcwotsmEPpazEGGRbt4wgdt5/eaNCVY6c21SJtxp7WLfd7jz31xMVwcLb+gEW8hxKHcZNM5W+3eR41DdK9QJ6+KG+paxPzxBaUVyjGYK40ft187ZsTchJ63FDjJDRk3TCVInC6gL/8iSup5yJaQe8mqeEnZheHdZgc5ix9ujrasVGunLa3xHCJtR1iIJAPNKeRB9wHZXJ6xT9Q3RtZ2+2QFvFiJWp3tzq5VZS+sjfnOiDASMdjBmdPhIdqD4cYOKP8K91auWVVT9hGEtHYjsGvcEk62UCkz93qELaMHYwVphMdMphgwM8oj/Hl9hb2pOqmQ1AIeh399m5fP3tD3rHttmx2z6RtLSZrnIFT/+TWtXrp2ryauh8zPaviHz3xYTrm5LELef1xz5AxLxGqR7lNpCUuOLBNhLsjYdzoremCV9cR1rK/5JnPkH8Gt18OOlbOcdi2A2c1YZ9gFo7W3fSr2YXQ1RR50uPA0F+NXj7FE+wwEcpxToonWgdYXq3Lkw5fPmxv7XNiRtC4+2XptZZyqbCXk+jWVKRZYtZPR/W6qhdaMwbJw8ubcryizrtqTP6wZ3FQyE9FIlhREEDcDH1bFZBRyLUb01XXepJvof5JAfsgGdaGEjBzyCD/thsjgNysD6grxiPbjxFY7ZVfmqG42R/vxAWerz1HR43HdWyeqzPIdgBgj31Lr2TTzrPqrqeeT8SlTRMJuQYIb1imFD8/wnCHSYSju9S/c6dK7bVvbN5FEULEZ3RUb/KBZd68akC81iBAznJYxkbBckK4jpcACQvc1s/TQhse7ZA/ykO4d2iNGVRooZdPC//2VKcLCTLJ7JB+1+oZwDt7TohreOWhgKfJ8yhHp5eR4Lco7cSLzTVSg09P7AWPe9vxDP2XCc74EySdZXvf3Xfs/dSEFe4/sKFx/D40HfTjl85iQyR76nZUMcKCN+heTNp700p8+9T3puE9qcVJ9Kybq+rPhW57Q+7kRfr3Xbd+HHALmrs+qGB3EES7H+S10LVc3/Yoi7TuvwOvbERKzusxTQ7r0oR6HZ7mbn0ex17zgiW/MLOVUGdkRFBjnnRkXkcDWhPT5l0iTzGaazsH2L3FrO1AILl4inAEsm14CtpZRS1sNUSrvRgjVUGBtaTCyPs4J+7+neohinnmPEQvfPN60g0xHv0ZA5hkYKcrR7CHLTRNFFwzNTq9Xf0+7Zcq7HxPJ01t45ug++2igrKKC6M/y8hS14cqgILzBPcmqzEX0rvfLco7uvfY9L8g+wX4m5y58f5b/3/55PwrwkLGymgoqUrbixJjOvWgtU8vsK0V6ZcGL6wxkMEBeboKVB75spLVIqc/d2uNwTrOabnltdUaRTzhcPVHCE6nmgMrOpgOfurNhECTjEZ5uAgbNIa2SXvk8M+hoiIp9H/64abzNfgsAnS3R7y7vjcavcdihFbcafI4hD73+b35iRAwfurr0vhmbIjoeee10VPHeXDNs+qvxV9wEh4+NKf5SswGoygx/sHczF+a6xo+owqA1IukfwpPQZRIej23av4nh7cqr2b8/YNFkwLAw9DR+01Y+4NLvpUD9Zv2bP/UrYp7sPl7qIzN1ftn5uRSgbrNHPxBtDvC52Y9ACKc/a8ilEU3gFKTENcZHUjnwtxq82unxqs/kkcuzNyY9zi+WLPL+2935DVoWSXLdOz2Fe8x/qZlcZLzrPrzqob3gxDD4skV5Q4O2fATOiuvlPrh2BPYSHdQExp7PT/Hfp626dzzsyKnEeizXMZf8TPDqGpSkUFua14zY+Ll952xc6IDPvcA5oDl3KmOfYYg3n4ha0RxrGeWyM2v8WfQmfEBIV9rEQmylFEfW52MBm+x1WlaDvLAA5lhOK7A3kAaTptWgQUnIL9Kw63TKhBQaa/uWN/BA51EI7NJk4K9Ndovgs3dOoJIt2rjy7128SShavHstyb9S75xMjiHgw+6jYOpgdHNg/lxPCt32bRJLwenLj42+eWucUPZRXw+/UJ/DpNoTcVYPgd09VKHlGpdvCHLRZBcY5UzhU0/Np6JybL12Y+oV5lXlb8ey2i5AztZMK35o/ZbEl4bjloCsrCc6bc93SQZABUkW6V5XF2SQtmnOMDMqetGigdnHt9bbOEm9WZeD81LVjK9PzBg5MmP344S302OP+Ocp9tpT8vavNg+5NnHti1cdJNLUU6YcDv+AOQUBdIyaN/GkC9X8+niyL+0/GatdajuU9Q9wgDJCikrf1N+lgMyyFFZ65QoHX+p2Qb9d0ocQ2PudbaWCXRJ/muu8MLHy3XYSatgDYeQE77wI+Yi0/i1J9dozXPBcyLmojzkBeGhTVAvvJ/ZSgBCOZLRHOJPKjnyZXKc2QpjywEW7symODD6t9rWy6hPlueMsOSEaEqSOPepXGPTerPIoOrnk+s8h+MbZXdTLfKaWReT5zylqiL4cqhnyYMqK9K5j95czgfONQpDIbDLXDZAmcHpxHY1D6v+Y/BALl4r8Vr0xNKKdYW1pIjQU3efBIP75wv5sdrbvcLmT0FA/PVNoV5wMHXv4aa7kmFHdj8c76XiiDHrCbHMte3rEu3UP/O3+iXyijEMl0l/Mvh13b1fIhyaGtvc/+T4/xgWFBtjrL/hLCzMRPUnzJsJIJGuTSkxx/YPnP8kKiD0XnarLBhC70MrEtt9FBEf467+AkOT7awcl3SUyezj7HBkWZzREl+n2+3mMfSGypBAhxq716n/bhYuz2wF9spS4db2GTvz74O6PvIjU0z5HTNa9C7Li/RW6q+bkrSM7IsF7LdQD0HsEVgatE0iXPgSF93NfCRl+XE404gV1i0zVOWpKc3aPNId5tX3tDCe05vj9rL3i4t0K1MlHnPvt9oqzRn/P5ozig4NAcPnMuduMhLJ8X/tcLO1//C1ord/jkvcevvw0Ux1EWox5Go6xDnoHYMIa451byLNdCGK5GzwiiMsZdhCGJrmOcBgclqO9vwBzZRUGPdvh0yn6fbmsosapWO9xr+EVar/VMhXeugmG51cZ6Ts6hJVfDSdtwKQdF8tmqUwvkkcnHW56ed+qjXOdev0V8xu8iMa5aWgP5CzYD9b9rHjnKYY1zYVXxU97npNjmO8+u6ZnpW3+Bc/yO9YeEIO2ZTOZiwhLS7dvsaajOE=
*/