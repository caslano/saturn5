// Boost.uBLAS
//
// Copyright (c) 2018 Fady Essam
// Copyright (c) 2018 Stefan Seefeld
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef boost_numeric_ublas_opencl_elementwise_hpp_
#define boost_numeric_ublas_opencl_elementwise_hpp_

#include <boost/numeric/ublas/opencl/library.hpp>
#include <boost/numeric/ublas/opencl/vector.hpp>
#include <boost/numeric/ublas/opencl/matrix.hpp>

namespace boost { namespace numeric { namespace ublas { namespace opencl {

namespace compute = boost::compute;
namespace lambda = boost::compute::lambda;

template <typename T, typename L1, typename L2, typename L3, class O>
void element_wise(ublas::matrix<T, L1, opencl::storage> const &a,
		  ublas::matrix<T, L2, opencl::storage> const &b,
		  ublas::matrix<T, L3, opencl::storage> &result,
		  O op, compute::command_queue& queue)
{
  assert(a.device() == b.device() &&
	 a.device() == result.device() &&
	 a.device() == queue.get_device());
  assert(a.size1() == b.size1() && a.size2() == b.size2());

  compute::transform(a.begin(),
		     a.end(),
		     b.begin(),
		     result.begin(),
		     op,
		     queue);
  queue.finish();
}

template <typename T, typename L1, typename L2, typename L3, typename A, class O>
void element_wise(ublas::matrix<T, L1, A> const &a,
		  ublas::matrix<T, L2, A> const &b,
		  ublas::matrix<T, L3, A> &result,
		  O op,
		  compute::command_queue &queue)
{
  ublas::matrix<T, L1, opencl::storage> adev(a, queue);
  ublas::matrix<T, L2, opencl::storage> bdev(b, queue);
  ublas::matrix<T, L3, opencl::storage> rdev(a.size1(), b.size2(), queue.get_context());
  element_wise(adev, bdev, rdev, op, queue);
  rdev.to_host(result, queue);
}

template <typename T, typename L1, typename L2, typename A, typename O>
ublas::matrix<T, L1, A> element_wise(ublas::matrix<T, L1, A> const &a,
				     ublas::matrix<T, L2, A> const &b,
				     O op,
				     compute::command_queue &queue)
{
  ublas::matrix<T, L1, A> result(a.size1(), b.size2());
  element_wise(a, b, result, op, queue);
  return result;
}

template <typename T, typename O>
void element_wise(ublas::vector<T, opencl::storage> const &a,
		  ublas::vector<T, opencl::storage> const &b,
		  ublas::vector<T, opencl::storage> &result,
		  O op,
		  compute::command_queue& queue)
{
  assert(a.device() == b.device() &&
	 a.device() == result.device() &&
	 a.device() == queue.get_device());
  assert(a.size() == b.size());
  compute::transform(a.begin(),
		     a.end(),
		     b.begin(),
		     result.begin(),
		     op,
		     queue);
  queue.finish();
}

template <typename T, typename A, typename O>
void element_wise(ublas::vector<T, A> const &a,
		  ublas::vector<T, A> const &b,
		  ublas::vector<T, A>& result,
		  O op,
		  compute::command_queue &queue)
{
  ublas::vector<T, opencl::storage> adev(a, queue);
  ublas::vector<T, opencl::storage> bdev(b, queue);
  ublas::vector<T, opencl::storage> rdev(a.size(), queue.get_context());
  element_wise(adev, bdev, rdev, op, queue);
  rdev.to_host(result, queue);
}

template <typename T, typename A, typename O>
ublas::vector<T, A> element_wise(ublas::vector<T, A> const &a,
				 ublas::vector<T, A> const &b,
				 O op,
				 compute::command_queue &queue)
{
  ublas::vector<T, A> result(a.size());
  element_wise(a, b, result, op, queue);
  return result;
}

template <typename T, typename L1, typename L2, typename L3>
void element_add(ublas::matrix<T, L1, opencl::storage> const &a,
		 ublas::matrix<T, L2, opencl::storage> const &b,
		 ublas::matrix<T, L3, opencl::storage> &result,
		 compute::command_queue &queue)
{
  element_wise(a, b, result, compute::plus<T>(), queue);
}

template <typename T, typename L1, typename L2, typename L3, typename A>
void element_add(ublas::matrix<T, L1, A> const &a,
		 ublas::matrix<T, L2, A> const &b,
		 ublas::matrix<T, L3, A> &result,
		 compute::command_queue &queue)
{
  element_wise(a, b, result, compute::plus<T>(), queue);
}

template <typename T, typename L1, typename L2, typename A>
ublas::matrix<T, L1, A> element_add(ublas::matrix<T, L1, A> const &a,
				    ublas::matrix<T, L2, A> const &b,
				    compute::command_queue &queue)
{
  return element_wise(a, b, compute::plus<T>(), queue);
}

template <typename T>
void element_add(ublas::vector<T, opencl::storage> const &a,
		 ublas::vector<T, opencl::storage> const &b,
		 ublas::vector<T, opencl::storage> &result,
		 compute::command_queue& queue)
{
  element_wise(a, b, result, compute::plus<T>(), queue);
}

template <typename T, typename A>
void element_add(ublas::vector<T, A> const &a,
		 ublas::vector<T, A> const &b,
		 ublas::vector<T, A> &result,
		 compute::command_queue &queue)
{
  element_wise(a, b, result, compute::plus<T>(), queue);
}

template <typename T, typename A>
ublas::vector<T, A> element_add(ublas::vector<T, A> const &a,
				ublas::vector<T, A> const &b,
				compute::command_queue &queue)
{
  return element_wise(a, b, compute::plus<T>(), queue);
}

template<typename T, typename L>
void element_add(ublas::matrix<T, L, opencl::storage> const &m, T value,
		 ublas::matrix<T, L, opencl::storage> &result,
		 compute::command_queue& queue)
{
  assert(m.device() == result.device() && m.device() == queue.get_device());
  assert(m.size1() == result.size1() && m.size2() == result.size2());
  compute::transform(m.begin(), m.end(), result.begin(), lambda::_1 + value, queue);
  queue.finish();
}

template<typename T, typename L, typename A>
void element_add(ublas::matrix<T, L, A> const &m, T value,
		 ublas::matrix<T, L, A> &result,
		 compute::command_queue& queue)
{
  ublas::matrix<T, L, opencl::storage> mdev(m, queue);
  ublas::matrix<T, L, opencl::storage> rdev(result.size1(), result.size2(), queue.get_context());
  element_add(mdev, value, rdev, queue);
  rdev.to_host(result, queue);
}

template<typename T, typename L, typename A>
ublas::matrix<T, L, A> element_add(ublas::matrix<T, L, A> const &m, T value,
				   compute::command_queue& queue)
{
  ublas::matrix<T, L, A> result(m.size1(), m.size2());
  element_add(m, value, result, queue);
  return result;
}

template<typename T>
void element_add(ublas::vector<T, opencl::storage> const &v, T value,
		 ublas::vector<T, opencl::storage> &result,
		 compute::command_queue& queue)
{
  assert(v.device() == result.device() && v.device() == queue.get_device());
  assert(v.size() == result.size());
  compute::transform(v.begin(), v.end(), result.begin(), lambda::_1 + value, queue);
  queue.finish();
}

template<typename T, typename A>
void element_add(ublas::vector<T, A> const &v, T value,
		 ublas::vector<T, A> &result,
		 compute::command_queue& queue)
{
  ublas::vector<T, opencl::storage> vdev(v, queue);
  ublas::vector<T, opencl::storage> rdev(v.size(), queue.get_context());
  element_add(vdev, value, rdev, queue);
  rdev.to_host(result, queue);
}

template <typename T, typename A>
ublas::vector<T, A> element_add(ublas::vector<T, A> const &v, T value,
				compute::command_queue& queue)
{
  ublas::vector<T, A> result(v.size());
  element_add(v, value, result, queue);
  return result;
}

template <typename T, typename L1, typename L2, typename L3>
void element_sub(ublas::matrix<T, L1, opencl::storage> const &a,
		 ublas::matrix<T, L2, opencl::storage> const &b,
		 ublas::matrix<T, L3, opencl::storage> &result,
		 compute::command_queue& queue)
{
  element_wise(a, b, compute::minus<T>(), result, queue);
}

template <typename T, typename L1, typename L2, typename L3, typename A>
void element_sub(ublas::matrix<T, L1, A> const &a,
		 ublas::matrix<T, L2, A> const &b,
		 ublas::matrix<T, L3, A> &result,
		 compute::command_queue &queue)
{
  element_wise(a, b, result, compute::minus<T>(), queue);
}

template <typename T, typename L1, typename L2, typename A>
ublas::matrix<T, L1, A> element_sub(ublas::matrix<T, L1, A> const &a,
				    ublas::matrix<T, L2, A> const &b,
				    compute::command_queue &queue)
{
  return element_wise(a, b, compute::minus<T>(), queue);
}

template <typename T>
void element_sub(ublas::vector<T, opencl::storage> const &a,
		 ublas::vector<T, opencl::storage> const &b,
		 ublas::vector<T, opencl::storage> &result,
		 compute::command_queue& queue)
{
  element_wise(a, b, result, compute::minus<T>(), queue);
}

template <typename T, typename A>
void element_sub(ublas::vector<T, A> const &a,
		 ublas::vector<T, A> const &b,
		 ublas::vector<T, A> &result,
		 compute::command_queue &queue)
{
  element_wise(a, b, result, compute::minus<T>(), queue);
}

template <typename T, typename A>
ublas::vector<T, A> element_sub(ublas::vector<T, A> const &a,
				ublas::vector<T, A> const &b,
				compute::command_queue &queue)
{
  return element_wise(a, b, compute::minus<T>(), queue);
}

template <typename T, typename L>
void element_sub(ublas::matrix<T, L, opencl::storage> const &m, T value,
		 ublas::matrix<T, L, opencl::storage> &result,
		 compute::command_queue& queue)
{
  assert(m.device() == result.device() && m.device() == queue.get_device());
  assert(m.size1() == result.size1() && m.size2() == result.size2());
  compute::transform(m.begin(), m.end(), result.begin(), lambda::_1 - value, queue);
  queue.finish();
}

template <typename T, typename L, typename A>
void element_sub(ublas::matrix<T, L, A> const &m, T value,
		 ublas::matrix<T, L, A> &result,
		 compute::command_queue& queue)
{
  ublas::matrix<T, L, opencl::storage> mdev(m, queue);
  ublas::matrix<T, L, opencl::storage> rdev(result.size1(), result.size2(), queue.get_context());
  element_sub(mdev, value, rdev, queue);
  rdev.to_host(result, queue);
}

template <typename T, typename L, typename A>
ublas::matrix<T, L, A> element_sub(ublas::matrix<T, L, A> const &m, T value,
				   compute::command_queue& queue)
{
  ublas::matrix<T, L, A> result(m.size1(), m.size2());
  element_sub(m, value, result, queue);
  return result;
}

template <typename T>
void element_sub(ublas::vector<T, opencl::storage> const &v, T value,
		 ublas::vector<T, opencl::storage> &result,
		 compute::command_queue& queue)
{
  assert(v.device() == result.device() && v.device() == queue.get_device());
  assert(v.size() == result.size());
  compute::transform(v.begin(), v.end(), result.begin(), lambda::_1 - value, queue);
  queue.finish();
}

template <typename T, typename A>
void element_sub(ublas::vector<T, A> const &v, T value,
		 ublas::vector<T, A> &result,
		 compute::command_queue& queue)
{
  ublas::vector<T, opencl::storage> vdev(v, queue);
  ublas::vector<T, opencl::storage> rdev(v.size(), queue.get_context());
  element_sub(vdev, value, rdev, queue);
  rdev.to_host(result, queue);
}

template <typename T, typename A>
ublas::vector<T, A> element_sub(ublas::vector<T, A> const &v, T value,
				compute::command_queue& queue)
{
  ublas::vector<T, A> result(v.size());
  element_sub(v, value, result, queue);
  return result;
}

template <typename T, typename L1, typename L2, typename L3>
void element_prod(ublas::matrix<T, L1, opencl::storage> const &a,
		  ublas::matrix<T, L2, opencl::storage> const &b,
		  ublas::matrix<T, L3, opencl::storage> &result,
		  compute::command_queue& queue)
{
  element_wise(a, b, result, compute::multiplies<T>(), queue);
}

template <typename T, typename L1, typename L2, typename L3, typename A>
void element_prod(ublas::matrix<T, L1, A> const &a,
		  ublas::matrix<T, L2, A> const &b,
		  ublas::matrix<T, L3, A> &result,
		  compute::command_queue &queue)
{
  element_wise(a, b, result, compute::multiplies<T>(), queue);
}

template <typename T, typename L1, typename L2, typename A>
ublas::matrix<T, L1, A> element_prod(ublas::matrix<T, L1, A> const &a,
				     ublas::matrix<T, L2, A> const &b,
				     compute::command_queue &queue)
{
  return element_wise(a, b, compute::multiplies<T>(), queue);
}

template <typename T>
void element_prod(ublas::vector<T, opencl::storage> const &a,
		  ublas::vector<T, opencl::storage> const &b,
		  ublas::vector<T, opencl::storage> &result,
		  compute::command_queue& queue)
{
  element_wise(a, b, result, compute::multiplies<T>(), queue);
}

template <typename T, typename A>
void element_prod(ublas::vector<T, A> const &a,
		  ublas::vector<T, A> const &b,
		  ublas::vector<T, A> &result,
		  compute::command_queue &queue)
{
  element_wise(a, b, result, compute::multiplies<T>(), queue);
}

template <typename T, typename A>
ublas::vector<T, A> element_prod(ublas::vector<T, A> const &a,
				 ublas::vector<T, A> const &b,
				 compute::command_queue &queue)
{
  return element_wise(a, b, compute::multiplies<T>(), queue);
}

template <typename T, typename L>
void element_scale(ublas::matrix<T, L, opencl::storage> const &m, T value,
		   ublas::matrix<T, L, opencl::storage> &result,
		   compute::command_queue& queue)
{
  assert(m.device() == result.device() && m.device() == queue.get_device());
  assert(m.size1() == result.size1() && m.size2() == result.size2());
  compute::transform(m.begin(), m.end(), result.begin(), lambda::_1 * value, queue);
  queue.finish();
}

template <typename T, typename L, typename A>
void element_scale(ublas::matrix<T, L, A> const &m, T value,
		   ublas::matrix<T, L, A> &result,
		   compute::command_queue& queue)
{
  ublas::matrix<T, L, opencl::storage> mdev(m, queue);
  ublas::matrix<T, L, opencl::storage> rdev(result.size1(), result.size2(), queue.get_context());
  element_scale(mdev, value, rdev, queue);
  rdev.to_host(result, queue);
}

template <typename T, typename L, typename A>
ublas::matrix<T, L, A>  element_scale(ublas::matrix<T, L, A> const &m, T value,
				      compute::command_queue& queue)
{
  ublas::matrix<T, L, A> result(m.size1(), m.size2());
  element_scale(m, value, result, queue);
  return result;
}

template <typename T>
void element_scale(ublas::vector<T, opencl::storage> const &v, T value,
		   ublas::vector<T, opencl::storage> &result,
		   compute::command_queue& queue)
{
  assert(v.device() == result.device() && v.device() == queue.get_device());
  assert(v.size() == result.size());
  compute::transform(v.begin(), v.end(), result.begin(), lambda::_1 * value, queue);
  queue.finish();
}

template <typename T, typename A>
void element_scale(ublas::vector<T, A> const &v, T value,
		   ublas::vector<T, A> & result,
		   compute::command_queue& queue)
{
  ublas::vector<T, opencl::storage> vdev(v, queue);
  ublas::vector<T, opencl::storage> rdev(v.size(), queue.get_context());
  element_scale(vdev, value, rdev, queue);
  rdev.to_host(result, queue);
}

template <typename T, typename A>
ublas::vector<T,A> element_scale(ublas::vector<T, A> const &v, T value,
				 compute::command_queue& queue)
{
  ublas::vector<T, A> result(v.size());
  element_scale(v, value, result, queue);
  return result;
}

template <typename T, typename L1, typename L2, typename L3>
void element_div(ublas::matrix<T, L1, opencl::storage> const &a,
		 ublas::matrix<T, L2, opencl::storage> const &b,
		 ublas::matrix<T, L3, opencl::storage> &result,
		 compute::command_queue& queue)
{
  element_wise(a, b, result, compute::divides<T>(), queue);
}

template <typename T, typename L1, typename L2, typename L3, typename A>
void element_div(ublas::matrix<T, L1, A> const &a,
		 ublas::matrix<T, L2, A> const &b,
		 ublas::matrix<T, L3, A> &result,
		 compute::command_queue &queue)
{
  element_wise(a, b, result, compute::divides<T>(), queue);
}

template <typename T, typename L1, typename L2, typename A>
ublas::matrix<T, L1, A> element_div(ublas::matrix<T, L1, A> const &a,
				    ublas::matrix<T, L2, A> const &b,
				    compute::command_queue &queue)
{
  return element_wise(a, b, compute::divides<T>(), queue);
}

template <typename T>
void element_div(ublas::vector<T, opencl::storage> const &a,
		 ublas::vector<T, opencl::storage> const &b,
		 ublas::vector<T, opencl::storage> &result,
		 compute::command_queue& queue)
{
  element_wise(a, b, result, compute::divides<T>(), queue);
}

template <typename T, typename A>
void element_div(ublas::vector<T, A> const &a,
		 ublas::vector<T, A> const &b,
		 ublas::vector<T, A> &result,
		 compute::command_queue &queue)
{
  element_wise(a, b, result, compute::divides<T>(), queue);
}

template <typename T, typename A>
ublas::vector<T, A> element_div(ublas::vector<T, A> const &a,
				ublas::vector<T, A> const &b,
				compute::command_queue &queue)
{
  return element_wise(a, b, compute::divides<T>(), queue);
}

}}}}

#endif 

/* elementwise.hpp
LII1CvvNqbA92L72J137VWH7hWF7w33t57n2Z137vq79V9eep72+bM5fkeb02Hsd9t6Fva/g2jsIWxPva50/bO3eWKumsPS1wtrfKnDIqi49xa5K97MCrtMRF3zp82MsKBvYKOlQg3qVNP2PtfI9NHQ22qHx8k6WGUNg9/E0qHT2Z+BrPuBKvrhjAwbOn3BGxzI4hbtNcbqZ+qS/4xfUzqBB4tgJk5bx3yGFjuMx1CUB7baQXqkaj92xAr6ZUMplbC7EzecbgxpK7nQ6X72cAifNR3tudVq++laUVDMWZ2hqcigJqMXBkNyNp3TW7sYlN1CVYG43+DKWPAjCzDfA/SUICoWi0F9xjg+mIIQSrPJZ3A2iTmPyOhmkCSDkHZddk8yhvAlMHa8j/IYM8Vobr3LAB/kq53Kkx8hf4pv51nc5pXcy5U/hRC8xQwDS3dmWZBhWHIqNYb+p47T2YuZGpl9YPulC9ShqTmXi6D124PqZJ2LgR2+P+zNn+jUoO6eAl5g4/pzV/LN6sfZE9jT88jmff6pPA4nY/IWx+bi1rq4xVq+vMWT93/sIFeQHWjc6Pu9zz5BPfWFqavhm+ikyJOPPkUE5xT/Hn9AXLoX4q0ski4l/urWVh21Cf3Fwpw2CCkfRCVA8RVrNmV0bw7zzFP8t/mQUesHEKKYwBU/pnTBGzphBKjKtS87DkgPA7+8bdiSL/m4Eozv9zh3NovOOY1G6l/wIFp0/nEVdd6Pzu/6WH82iSyH/BszPDWPRbwPD7yJ7akTRV8EXWw+C1RJ3eeGrGXUXNMQWzl5GN5EueFtdyf7wl5aKq6d52l7XsmIWkImrfj4Z2p4JWYvVtx/UrbrifHwNfxVh/Dl8sZK+FOifxJccYnXLlsTm1c8+N9aEez+NvoMa6Wp8fPJIXGQ+Gh+IrPD41YtD2ZAqL+JVeJHKCl4mIPajCvpmIF0t96hh/rFh3mOYf2KYH4M5I82PG+a9hvmnMK+V5p8Z5p/DvEOa9xnmX1SQgcy/NMw7yV/xfMcwf9cwP2iYb/EC8y4Kj3geMszfo/CI51YvMD9M4RHPbgqDlKkMZO6oDGQ+URnIDIkIGcDAw/9jkAejkQvIiYO8gyoOqqzyqiqqKiNepCJSWekhIyorvIqKispnn33uueefj1RWQVtw798s0gX/8K+SvhUo3G6jeytpnRLZLL4p+Kz8duBzPD/w+zwjN9KTl3pu9oSeU6X8j6X8HikfIT/p0f5TfhvhyFDxCsKzlnAqXJQuFDYRPgKjCOpw6vSh8JKd3FS4Sb6aifA8ehSLfhR07rEs+m5Qy0gWHYY2aCjcpiyIRA/D73z52412bANkVfqlYH7LMNjL1OP9i/QcWaCn+DbzP+3pq/0yG27cXtynLO0sKml3m6cmx9QZXn45LYZPHn8Of4Mkle7WW1VyOYzEiulv+9Urlo4K9JaSFh05vrFhRm9Wuiq6EWTr+Na0U5czWRfeAdr/+wjb//NIgdtQJu4LXvaHCFu2L8LaWfnPzo6q6JNPR6hcsx1VZX/zZ+AZeAae/6/nyiOK/drU/+6DJfCmW/58cNo7Pnr+V49+4FeH3HjZ/R7v70LXFOimC9kzjF+V47vG2q1n2hnjxavX47NJfodoUkmgH4XAwtrTMolm5e9MIvGMZAPPwDPwDDwDTzHPP+R35R6h38DeNTgSNe17LPeJQ9zuJx8cic47uNB9r+H+YhTflji8uG/j/T8/ev7jVdH040b847TsxQjb/NcIe/L1CLv+cMY+egRj1x6Fb3FgInQ/zE+MwVkj2D8E80a4T0JKf+cYfJsT7j+B2xdhPu5YxsbD/WTsJHwGE/C3jsYaA9yHwf0CuM0=
*/