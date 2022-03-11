// Boost.uBLAS
//
// Copyright (c) 2018 Fady Essam
// Copyright (c) 2018 Stefan Seefeld
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef boost_numeric_ublas_opencl_matrix_hpp_
#define boost_numeric_ublas_opencl_matrix_hpp_

#include <boost/numeric/ublas/opencl/library.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/functional.hpp>
#include <boost/compute/core.hpp>
#include <boost/compute/algorithm.hpp>
#include <boost/compute/buffer.hpp>

namespace boost { namespace numeric { namespace ublas { namespace opencl {

class storage;

namespace compute = boost::compute;

} // namespace opencl
	
template<class T, class L>
class matrix<T, L, opencl::storage> : public matrix_container<matrix<T, L, opencl::storage> >
{
  typedef typename boost::compute::buffer_allocator<T>::size_type size_type;
  typedef L layout_type;
  typedef matrix<T, L, opencl::storage> self_type;
public:
  matrix()
    : matrix_container<self_type>(),
      size1_(0), size2_(0), data_() , device_()
  {}

  matrix(size_type size1, size_type size2, compute::context c)
    : matrix_container<self_type>(),
      size1_(size1), size2_(size2), device_(c.get_device())
  {
    compute::buffer_allocator<T> allocator(c);
    data_ = allocator.allocate(layout_type::storage_size(size1, size2)).get_buffer();
  }

  matrix(size_type size1, size_type size2, T const &value, compute::command_queue &q)
    : matrix_container<self_type>(),
      size1_(size1), size2_(size2), device_(q.get_device())
  {
    compute::buffer_allocator<T> allocator(q.get_context());
    data_ = allocator.allocate(layout_type::storage_size(size1, size2)).get_buffer();
    compute::fill(this->begin(), this->end(), value, q);
    q.finish();
  }

  template <typename A>
  matrix(matrix<T, L, A> const &m, compute::command_queue &queue)
    : matrix(m.size1(), m.size2(), queue.get_context())
  {
    this->from_host(m, queue);
  }
  
  size_type size1() const { return size1_;}
  size_type size2() const { return size2_;}

  const compute::buffer_iterator<T> begin() const { return compute::make_buffer_iterator<T>(data_);}
  compute::buffer_iterator<T> begin() { return compute::make_buffer_iterator<T>(data_);}

  compute::buffer_iterator<T> end() { return compute::make_buffer_iterator<T>(data_, layout_type::storage_size(size1_, size2_));}
  const compute::buffer_iterator<T> end() const { return compute::make_buffer_iterator<T>(data_, layout_type::storage_size(size1_, size2_));}

  const compute::device &device() const { return device_;}
  compute::device &device() { return device_;}

  void fill(T value, compute::command_queue &queue)
  {
    assert(device_ == queue.get_device());
    compute::fill(this->begin(), this->end(), value, queue);
    queue.finish();
  }

  /** Copies a matrix to a device
  * \param m is a matrix that is not on the device _device and it is copied to it
  * \param queue is the command queue that will execute the operation
  */
  template<class A>
  void from_host(ublas::matrix<T, L, A> const &m, compute::command_queue &queue)
  {
    assert(device_ == queue.get_device());
    compute::copy(m.data().begin(),
		  m.data().end(),
		  this->begin(),
		  queue);
    queue.finish();
  }

  /** Copies a matrix from a device
  * \param m is a matrix that will be reized to (size1_,size2) and the values of (*this) will be copied in it
  * \param queue is the command queue that will execute the operation
  */
  template<class A>
  void to_host(ublas::matrix<T, L, A> &m, compute::command_queue &queue) const
  {
    assert(device_ == queue.get_device());
    compute::copy(this->begin(),
		  this->end(),
		  m.data().begin(),
		  queue);
    queue.finish();
  }

private:
  size_type size1_;
  size_type size2_;
  compute::buffer data_;
  compute::device device_;
};

}}}

#endif

/* matrix.hpp
xylxDj++ThgEPSw/1Z4Vg2qnLxBzMINcwKLjHaDhtKXHJTzmMXCjtAgeWH5wAqi4QcvqjYUgUMTOR/fS1JU0tCEP9OHVt0B2MS8DcA39XJo3qk/tXHxvdzpv1JClKvqlMxiWv02Rf94rdmmN/dE9d8uu4pL2Wuq2GcIBzGhT4uu0Th4NOjkU0jYwN08MaI6cHvW5G7wpsy8ANde8SxRHvBbmq5Lf18Aqjk44Xv8t3YhSzqgJfh0YZPvDqR5IiRDzsm6zTWcwL1vywmddP5TwQxsy1lJaj006SUs0CumBV6kbBmUP0qcCPSI0EGFlG4nSelKl9qLETLu6GFDlM+0mbTnayyLzcgpRYjh3VbZnX0a7SBsEboMp6TUf+vJo3TtLwghtgPPMXnc+yMxdDzZ8nbKy9V8HnTNpi5adO72qy4CkHKqPBXqmInJuA7yrOU/zo9GzWg3jJ8RUkzFeK+MeZKMFwhdM963cp1x93tXcTPfZgxQTQa8nELgySs2Z3v+Jqr9rUX8riRLPBvgHTgH8+Ff2AvSKIKLP2skY6zoDwMCEKkI6SaJxC1ZzlYtm+nwsus7zmlETi58HPM4xKepENE7egn09eH7yqtHLrEmZqBKsAViDiykAXsqhu1g5CnKRa8CSI6jzFnhJ/0k6XOCERtUH9rj+3M2DHG4lPIGZwJUOUQcjKds2DMOYsLHWcfjRJoV5eYMrpsk7FBUvmeryLSf/cDYHxVKwihH1ZsgE+gWoYJplfXwH1Pha1KuEV8+HqCcQ0ATkYMaNCBEKw2FqZCE6umbdHqyo/BthESGw3zMUtfh5coVZgeKPm0k4qsgCSGNiDZGElPNfVf+gYM38oQkuRVR5tkSn68GleXp8KfqTNCR0zuVMCjw7WvSbx6A2vzTCdr892BI+uDZviZMejxSw29BTC+AU2SoGON7dsZU8aPGZA9EQItMAB9YYvjC89Clwg+S0pP2opjNqgZ2s45dbXqe07iS9UC1j+sSQ/NgMn6g2pBv9tUdwAYbsQBqV94Y+W/lFR4u77sl5gHex2kwd5/ijlTxqeIzA6mlWPOkjDQYMZ2SzsFZlO4vAN0CbugJbUxpaqb8K1MBuCoLqSGJcsIDQ1UXuD8iYzmSPpjhVIj2QFPAudLJR2T4kVudPmSueXU52y4cUJ39Mg4XY1tk36NMjPV1Rs+2mJCG/QdzhSyZvghl7YtLUGKnbCwWO1Uet3ydwIu5kQM81uof77Aq4Jk6nXgnf1h011bhDJKnPW4HK2NN1FREcmbYEt5PJZW7XR8arHRjX29KaO0V5HXqxxCfs9Z2joYx7xlOZx5hk3ei2vcrgH6KA3/kQC4h/xNf0CorE+hW15bdos3a8Yea0MwnwdG1QTmZ6azu4zCcLQcYcmstKMzs/SnlM5FQ9xpcfrx9O1ExC19y9htvkXVN9Zh7qB6wT9umxb6i0+6JegukTsHNbp7Y3g0c3U2Zi9xxcAWC3sODkImPn70KVZXN3/tasdT4zH005ugv1c+LqfHXeQW1XunNLxc+630lP9MQeQr8voCt/+2zDvtwkoDoCfHlSyBcdXozEcNIeArz76/0IqfHFmxlybQIPwNYmojey9fImsvVO2yS7cYN9rxc3AbLSOQJPas6ckPaPytUPgCfR1jLstED2zXnHxBesdAhp6V8996ybP2fv5hD78ao/4tuEBG9lDV0QvFHNJQOiAezon8wwfr7smxReSz6sUtsI8h8+fjOzzqqsF2+c6Z7L/nwcttarOIdIM+TTlxTpduoPmk6F7b8qvMUOAibomEjTqTkmK7zwjx8dvpI5/4PPwrQ7oAP7iXRSwwhW9HqGWBHJS3Qd66t/sasLmyspfB3W/bPcc0zfhkHSot/F/mABZxSUDzNADZskGhPbBvnwfpWdMUoHLKLxErXOBFtTzxY58TxUkqnxfLnXsZv1QPZDxzePNKn0zasXqinz4nL4YYW5ZwouHZOFcfSQekr9dDXXumaWyiPjPKVq8FIoNOVEcNYuMFknP8kgM14H5cifQ596mHHr/rDD3k29XWFhNKkloL+bvKMOx2bcYgB/guCKkVvLpNQ6mtuxpfyIF3NaGQrDORfcuWqNrFgNZcn7Rr9obXvgHYAnfT2pNBRQFkQkYTYTBDSjMNPcq99W+mBH2+ekGdDQm/31KJLVAA/THSmvkigfPi38txTdJVNegD8lJ8OX/lBC7XREw1LmumfuXre/4VbAFLipKUUkyrCdnh2bPq1cHylV6C4Bv6PUyV0UBD8gNj2CLsE2E3/LcZKLd13RwvObrnf7+axoXO0yWTHBCw3shTTkb3y9BbNPrzJzcEDVyiqPhYrrzIKKaCkaJ8drKDtuBiyKG2fdjS9QwL/Pg07tRj9XV4rEtAfAIFWARf+RcSt2O93GnhWa89MPc+nl1ckP9q/BRg3rsehMebDXdenlL8F7FB5JWTU1t6Zdu3UEzsrYl4BjWvQPRryKb2ISAOJu7tprKtFRebpaDs31oKzUaNQGUN4OqmsZ6npGoc6lK5wbua/26H0vrzaKHyG/eJFviOkPfhSJOKof4hmEY7CYGpjixo5Lr0rMbrJr5IluFCa8PzfqeIIxA4QO6hc3+xbIjBkKWKZvLtjG8fZMuzkJRxEosQa2dPSydLZiBVzv3n7P1gUV8M+WTX6AeGa9+V4DhSr2GWcV7trUU8w+R1amyB+DANRQRxwaadMrMnpnMhctHzHYBxU0KdqQGL5/Xmkno2irZIHx4NZEe2SG5KAFvTLZCQB0F/2rIZwFwEmyxFL2UAl2IkrzFVfe5kyqMeCMkFOSoQN1Y2PmIQNVZ52IeH64oHK+1b1F3fpOFnTu3sg9ZUNKLmORQqTa4zon/uqqkc0W+2T+hBtuNuZklzjJ5cD4wZ+R9Mjffwl3KnqGPx0XbzyqfA+Y17Xm/N2U478mJ2hZ0cfY/huPwU8dC04UDX6lf4q2I5HS1lL/wLwph5uTL8SHkn2XW/8zwR9lAdYB7GuDZCSiSrtRveDyJ+jO0S3pjDrwIkNd584VWU3V0B3K17F8wjveV7B+biD2wTUmJ2dU47hkEnPyriWvUXL/tUOpLvh0W35U6nATtCwfop5GOu0L9yQLYDVxRPhsE3hDZzrKnOtRk6p5xw8lCucFwdqxxWDWuK5M6A/G3hRP2aJnDSHqP3cfc++IuE9nGJbmnrhPlE/FFmTT4zpUsJljdR3lWiUTs5iQkvNlomlAG1EuPbAlyMDl03xhP6YhrzmXWhCEf3rzImWfhftbjSDmjHiiQSuZcRFsK0ilyFH/GghprnMT+ORZTLBQQJdKu9VIg1GRPvLsfYlYvQStyXE5IcP6eclpSkODD7UB5RhV/s3sWP6UAJ7idmsvYYxPijn0Mx9MMwElQIUY5+9XQJ5fI0ZmC8ILHbmj7uz6CZaTHGZIDQ9xDZ2mwmEd/vsYUf14dEzpi/AnryVVCag6ipraz+BZN9C8amjTkguYgt1p8nhQrAVGuspPGdONOt2grGAE//o4069lzHbQsfZu238lFQZG5BvmwiQj5X0lmkjZkKmQkngO3MzhSuybgRmcob+eR+HCn4B4CeFdJM03tYykN0eN3lA70xCcWbt79Y7Khp9NKDgx94QrMNPzJJtnSs9G3799g+aBn3MC52FbeHDy7Jaa6ZlrCMuemXcC4ymZfVDz9H2qgMsuevxk454r+YDSLoPonGSOwwcTL8iI5p9zd1nHjPelSSTDlk3kgSUQf/i8ybFG0AUy3MC3RRDO6dsjp87jjgkE8JIbOSp5w08aR7dMGgk3JTjGw8Qvt9vJcnwnReVW9gNbuiElT+6n2ycn45PMGYX4EC79XO7gorlJPaFLgOph7tIxqPvkPs+BZORlt4KQhil6Q+VI9X3ppJqifcjrGOuVPmuQ9EH8StibSer+OVnDfYbvIYqFYdATJbjRwNHNezzkj0kd/mvtP5zDZasX8zM4Y/g1g2bZKGcd22T0XvSxkzJe4y0b6MtU+xlsYvluo1N8XEOXxLzXISmB3FMPx8ETfTozfqYh7Cc2cpWxF5t8+3CL21yj43fzJTHpdy0S/Tz70t04sVPyXFVfcfZVD+SXMpzCY+gtUojfUPFBPlZ8Dc8KxKsoQdwFbPFc+7yTQ6crY3074goFRdDK2FJw9B4Bf/n4Gh2Co5P3c6QQl3NgQKZCe2iwGI8yHRgzhStPAyXNbhooq501Bly7lREHdj54zeKdE4JXgIt5KLFmNVWwxtB+0BMrvXXYAngtR2eHECBhYJfT17K1S4sZgsPHAqwyPvNO4Pr45YtwbybdvSmcV97qbEEzMhKeLiMYAgMlTiTDOB5OpqGET6N2KvCVwiowhS+BTHQYmDgNOZdeMht9/U5xP3pHSLYueL+/q8N4lvS5jGl4DPJywLQu7ljVVsETGnSUQ3qSQ3pMd0nQw6irBLSA8GfOTfNmGOH7TPinY/GT8f4Pahf5GM7n80i+GfcJUMzKwhgN08r4iTZGTCTPXfcQZIYzgyHA7sut06fh6cE0Ud+Zj1uqAsQpMf5WZZt9e1qvTM9LgJ8NIidYphswAM1kcNGKRyoTTrm1z/E2kBwSOrNNJohrnJ802R3qsuaBnq82juQDXBisn3qe1qp7/t19qsxWd7ikpnWPDM+2GNWZYH5P9HvMsGSEDA/reY71pTyrtJDUyC6fbuwX/97FFmkrFhQqZrZtUlGwNo0YEqVhndygoZXy0LNOsSHHKAeUCmOssZwMS5c2nHI48j+77qiWgV73v/tvZ+6ZborUw6Ouw/lmFxy3H6RtDX95wrKqcFhi289fK5XKq7HGx6ZEVsYAc4BKqiOPxGEPgxb7i+4kPdPgM3BbGVhLxx1zfZKn447S06myLkV/xo2IpvBP8ZSZOgbP/AMgowXd3/3DHrPiwBYd0FBbvTppVMLr3aKUS8SECz9iLuWlPFbEv8P3Bw4hT77to2UfHTk0hL9m4f8dysUrgAuTLTCsTQsQLuaMDO089n3daomcBthLxtrBFjCHJmavVcqvL+DIWsi4hsPVGDOq/sNThdxQIF0oRfrjdQ7TljxFa9AkPaApq61sadFBscxYxUOlzf5nplmY9bSqVpNVO0pfx3AFt4YVigBVgAgr5gsDGqllyogdgM8+mjVTUncgv2OJpuC03pnoQPm1ZCeIe8aaPpuUkOywqIDi4qNLvG3OEPZsESr4+w2jJe3BDhernA8nOXhq1U9A8EsT2E3Xyfjix0HA4qsYmkoyjFYWook9RJOm6wrRc0PlEtyCIOUa8JNoPTNnmpa6wMXc1xKN9QmCAkx+qYxi3+hu6G+B4cYLX0Ejj/KBnilixb8gbfrIYXaNCj6cufrjZ1xEq4ufTEYwZTLQkYLllundKg68Cxpxh7h0MQUF7qFGy7OpHMBRWaFN0bBR09HR9sLzHgqo8Qhu430Pw4D6KK1MfOU0rg83cJX9nwazxVuXjjIaSISZBxnBIEwUn6Y8I6ZRrsuXNIGS4ThM59yUEMxHRhFtSV/U3e/vDEHTuEdXsO7oHRQDsC/7tr2XdIGcbrRF+sD3w3/ZBGlJP+mDsoRAkfFtVPdYoJpZXJ+8HppIVws5ovp9ICtz6rM51NjBz5l1Z7Xi7fnwKNNxKqKSu8AhysON8p6kQqkIqhOYGlkg+26I2EghCXDUN+C21nGU7o5m8ibc+MrzxpPROxRW3PMytF4BVLDujrH9z3ZUJnMWEn9jS73y/hXbgbOVXvgqVUayO3/liy4VkrQ2KtgauSjLzyJpLn1H7rBA4F0we+BMcpO4Hr8jX4Ff1VstP9aEpYNJssh81fnItOg0FIsRWXJ6y1dauLnLdK4ebIRYQEbBFyrOfKFUM5dRm9nIj2I/7L6FvdGJPezUJQYP395ROqL9oZnQMUJdOImps9yPkp9vlJx1q1yPuKRKJm3C5VHlIWZ3A++jLxfeTeFabKgCdiu9KGsV4ul4lZRI4P664UpMe64ixuJKD6e1WUIQcDjDIqIoMUJs1IcKz/3wMg/L5Qtzqr4GePkx0hEHkbDz68bbTq6MRBCAZ/0phhgPRxC4C4/GIjq9aaH22W4sygOWYLTqGWW8vsDmSjdoyYg/EX/Te4u9N3tDLvqcoXwTYrw7x3iq7y9jwL1jkWb2YgmB5PAIeaY1hs/YKxpn4o5SAUv9NpI2DwEvMtfZfctjNJOHjRxmFqYqGclgYT+YzN0ZwWznQzAzJreyD1E79JeS6AUWsRLKJOyqGm7x08Tuw5wM3pnCnJjUzFQwVzhukY1MR4jVWH+KPMgX7cGR/PCR9ApZpftKYH4/8q0Dj3ELxXN/38nzjd+uHmqB/+TK1wvJ/tmS/HBMVu2ZxMBlkBwUT/Gx/pc/7Y6M6nLYX9F6p4QySD0fR4nHROlaxfbWTdw6A2R6k4Ddn6poaGKUa+pWgNDt3uqo6u4p2stT0YVIv+Z3kw2GWNLy/QcLniPvPTni6SjoHJuNmpuHOA5TA18lQW4paJm7funhufPSlTveRzeQvBnu1Ye7Tu4wPMgWizueVNFvxYX/a8xKkJuwywd857g6fDf8sKEng/w6u3QIGbmhn/wq3D/WTcHtn/IUVmEITw91Z0UDUJkX1pHDMmmFAEvHN4tMlm2UOH60+E2UuF2MuB9WvC810Ze3sKeC8PtZ2KOQBWx9W5JbRjq+pVjpShCjrZLV2eIGilcBfY3E8mgFGFtIDRKCl25rE66dj59oYItp4TcvB/eNwn4VnTRWpwly2+nM7/R41whrKWw5uL2iyxG5XR4u3qEN3bG3uFO9KAVLS5EEG/NJwDvPECpAwbrEKcIwLwLmZAVyGrxSx5oVqYkAxpKbBtPFKSJbXWWs/yrb94U+gi8JwXgrJmUkBg8Cjb731u9UhL9KV04GU4m8afEp1oX5hNidV/44hZ9X7rgGT7eUsnzbF28SOMFCq16NtBpICbEqKjKIUGj2ME6lzyIlysZqbUrEIityAvr5sniVlbbc9UTMRg/4OVq4fWJJDzW2jdTWS9hrlUY9rYYlV3r9VJVhnwo/b9wzBqpZCjm46uiVtGF/n4GZnAs5CLHe9bVhn3uUsWEH04emWQwpyIjrDVy3h3FGK014rSr4FnnV/B1Sgq5cDFlR/Gjae1r8rQdThTa2HFBoB2m3GmCY1dz9BJJhB9OGXrQYYLjV1K9i3xbX7362kWexhf9WSpugU9ZnjkH/Yw4TfYZAPUNhJRexSK963Lg3OH62bm9oUsCaqb52sxCETK1mMRCexLccgkydYv6bWTX9llj9X0f3/0D0AzbLB/ret0e6veERlQ173f3Ib/sR0v8ZzG9gLIElV5Vd+e3G/r/xuy3i3P10STQpt4XaQlMcp6BQ4gpGaX7wuktPRfnf3VIuN0xM9rImwptWMPuHcQ9Mjo9iXiwztEwS1N0V9NQyTeIfVMYa6JzKfVlTgja1EWxCUly7IJR5UYjJLVZhWS/gJZ4lsPUVng25MyXiChIl/W/ofEr+ofJs6B0DRrDMgSSVAMyBJddNY1KZBFfbVs8aHqtWopjWaMcuwJ/uBkQr6cZ9N/bzRRaWBVcbdlr+tXw5HSWnSTcdLSf3EErqjB07mPJ0TqdUw3rf1bPEz49o2RKiDEErg5Iw7LJTWrbSlUowGKUchFEeb9WnslMDyVi2jCUT8BzlIL+ZRKVXbOJKMNeMMpjoRMaG9VSuF6mCCKqbSA+Jfj81jEQzgg7oJJOvErjMJEo2rbJY/Zuf/O277plNgpanaQhvv1a9s/IXclCu/PdX4JPG0n1yn41ySLm5gmloy34lI3vcj14NmWrG3C57o0DTL4icAtgZ/tdejnTtYLYb4C5Rc8cjzCA9TF9J1n3yL5UuW57vGktCtw097KNOsZBycKMneSJqyBlaoSXk+gcpFP9Xf6COeOsQUgFUjy0ob4qqIjqFm11p/HLTmpX+czw+5a63HvvwdV5MRuWu1MddJJMWVt58HrV5kwXuW2Ffeu3mYPWSie7nwhloo6zlyN+JkdUC9H9cb2/Q/N2MncGmPxFzS2HLVh7kLJWCki+XseXMByBfJFoOPHDmfe/kOt+UCC0WvJ6Gi6bp6GLl65LS4eSTLVQSjo9/GwktMvoZCuuy0tgtI7BgT7PPla7PSyjs4ids4+Un41UFcnFSH7OgVHEWcRKiGaaV9z3aWA4c9znqFJrz4VZCvLiBV2i8FvVBTYsELs2vcbDvf67oPwU57+u77NQFLnHaH+6GPegFLgmRWNQ64g2zq2+1VAUu7tzDKy6bxIr2usIpLrg9EDy58eIWDl/QmthQ0ddZKR2mjbgvpgQyk+px9v9Qw2SR98hLxW+AU35kVIMKoJZ/gVNC/fGISz9c9mwC6UwtJjuYsTi/3s4p1lVYTS5mttq4bshjwsecx/SHeYvqHQQ2MAM5Ne8L8BnH9Fd7CTcDYcRLbj6DaKt0sVRI5VWizW5jFgHhGslW26hAvDDrqrGSxxd3oJNFNb7sXsf3eDw1zwrQsdIRO2HrXse1UJlbn173h11pLFe1HFAy7+aWt1iMY7GsOC1AjUBIo5fnKUX7ni01NG1Qh2fQ6/G3PGaBVYZHMvjrSZCJl2t6bAS8qBV0Ag+mol1r8rcf1OmAy9j2Q9/GCGkPvsm8/CkFgpe/YUNX7BXD5rUD4oaHX6NDCic3mYFjh6089VPaT4QACiz105f0bpw7dMuhuaBrfQbNSpP7if3q3nLgJG89owxWTrhpfzbEbxNzdwAQT/Cu6wo3H+MFm4KVpp01ggtNB3tI7v+Aun6bqd7oh56VVHRPHvNQr2rxneJYeDn3r4FRaCerHOYfn3d5MlJLUB9YSXnTBLAYlkrUBqXK1OvU16LiV4qvJaVvbo4mjuqjEnxizTsl8J5sQj8H3W18YH/Y1vbBvIdMsWigxXUS0z2zkbdAQjml3KdU17byF6QLKu3ho+L9fH+4yJgUtMSNdz4vC4p3pwQpfLIvEszO9FRCi9PDuvlJZXFN5yq1yyabzxLSUUP3uL1XTY2m2WdTjeYIzUUFXozfdUWydeyjCvLRdrcl7vCjCqfP7M4fYWfm7Ul4721H3WnHtyW4hlva9EbxPkKETmfRakOfERV7Az2PCWQJB01Bz6LY5scRqog9aqxbQWYBP9vlQUZE8PWiV2hGKDbnKMGWHX7CdzZ598a3Tm4=
*/