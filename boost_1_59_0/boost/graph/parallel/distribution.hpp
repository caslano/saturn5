// Copyright 2004 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Peter Gottschling
//           Andrew Lumsdaine
#ifndef BOOST_PARALLEL_DISTRIBUTION_HPP
#define BOOST_PARALLEL_DISTRIBUTION_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <cstddef>
#include <vector>
#include <algorithm>
#include <numeric>
#include <boost/assert.hpp>
#include <boost/iterator/counting_iterator.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/config.hpp>
#include <typeinfo>

namespace boost { namespace parallel {

template<typename ProcessGroup, typename SizeType = std::size_t>
class variant_distribution
{
public:
  typedef typename ProcessGroup::process_id_type process_id_type;
  typedef typename ProcessGroup::process_size_type process_size_type;
  typedef SizeType size_type;

private:
  struct basic_distribution
  {
    virtual ~basic_distribution() {}
    virtual size_type block_size(process_id_type, size_type) const = 0;
    virtual process_id_type in_process(size_type) const = 0;
    virtual size_type local(size_type) const = 0;
    virtual size_type global(size_type) const = 0;
    virtual size_type global(process_id_type, size_type) const = 0;
    virtual void* address() = 0;
    virtual const void* address() const = 0;
    virtual const std::type_info& type() const = 0;
  };

  template<typename Distribution>
  struct poly_distribution : public basic_distribution
  {
    explicit poly_distribution(const Distribution& distribution)
      : distribution_(distribution) { }

    virtual size_type block_size(process_id_type id, size_type n) const
    { return distribution_.block_size(id, n); }

    virtual process_id_type in_process(size_type i) const
    { return distribution_(i); }

    virtual size_type local(size_type i) const
    { return distribution_.local(i); }

    virtual size_type global(size_type n) const
    { return distribution_.global(n); }

    virtual size_type global(process_id_type id, size_type n) const
    { return distribution_.global(id, n); }

    virtual void* address() { return &distribution_; }
    virtual const void* address() const { return &distribution_; }
    virtual const std::type_info& type() const { return typeid(Distribution); }

  private:
    Distribution distribution_;
  };

public:
  variant_distribution() { }

  template<typename Distribution>
  variant_distribution(const Distribution& distribution)
    : distribution_(new poly_distribution<Distribution>(distribution)) { }

  size_type block_size(process_id_type id, size_type n) const
  { return distribution_->block_size(id, n); }
  
  process_id_type operator()(size_type i) const
  { return distribution_->in_process(i); }
  
  size_type local(size_type i) const
  { return distribution_->local(i); }
  
  size_type global(size_type n) const
  { return distribution_->global(n); }

  size_type global(process_id_type id, size_type n) const
  { return distribution_->global(id, n); }

  operator bool() const { return distribution_; }

  void clear() { distribution_.reset(); }

  template<typename T>
  T* as()
  {
    if (distribution_->type() == typeid(T))
      return static_cast<T*>(distribution_->address());
    else
      return 0;
  }

  template<typename T>
  const T* as() const
  {
    if (distribution_->type() == typeid(T))
      return static_cast<T*>(distribution_->address());
    else
      return 0;
  }

private:
  shared_ptr<basic_distribution> distribution_;
};

struct block
{
  template<typename LinearProcessGroup>
  explicit block(const LinearProcessGroup& pg, std::size_t n) 
    : id(process_id(pg)), p(num_processes(pg)), n(n) { }

  // If there are n elements in the distributed data structure, returns the number of elements stored locally.
  template<typename SizeType>
  SizeType block_size(SizeType n) const
  { return (n / p) + ((std::size_t)(n % p) > id? 1 : 0); }

  // If there are n elements in the distributed data structure, returns the number of elements stored on processor ID
  template<typename SizeType, typename ProcessID>
  SizeType block_size(ProcessID id, SizeType n) const
  { return (n / p) + ((ProcessID)(n % p) > id? 1 : 0); }

  // Returns the processor on which element with global index i is stored
  template<typename SizeType>
  SizeType operator()(SizeType i) const
  { 
    SizeType cutoff_processor = n % p;
    SizeType cutoff = cutoff_processor * (n / p + 1);

    if (i < cutoff) return i / (n / p + 1);
    else return cutoff_processor + (i - cutoff) / (n / p);
  }

  // Find the starting index for processor with the given id
  template<typename ID>
  std::size_t start(ID id) const
  {
    std::size_t estimate = id * (n / p + 1);
    ID cutoff_processor = n % p;
    if (id < cutoff_processor) return estimate;
    else return estimate - (id - cutoff_processor);
  }

  // Find the local index for the ith global element
  template<typename SizeType>
  SizeType local(SizeType i) const
  { 
    SizeType owner = (*this)(i);
    return i - start(owner);
  }

  // Returns the global index of local element i
  template<typename SizeType>
  SizeType global(SizeType i) const
  { return global(id, i); }

  // Returns the global index of the ith local element on processor id
  template<typename ProcessID, typename SizeType>
  SizeType global(ProcessID id, SizeType i) const
  { return i + start(id); }

 private:
  std::size_t id; //< The ID number of this processor
  std::size_t p;  //< The number of processors
  std::size_t n;  //< The size of the problem space
};

// Block distribution with arbitrary block sizes
struct uneven_block
{
  typedef std::vector<std::size_t>    size_vector;

  template<typename LinearProcessGroup>
  explicit uneven_block(const LinearProcessGroup& pg, const std::vector<std::size_t>& local_sizes) 
    : id(process_id(pg)), p(num_processes(pg)), local_sizes(local_sizes)
  { 
    BOOST_ASSERT(local_sizes.size() == p);
    local_starts.resize(p + 1);
    local_starts[0] = 0;
    std::partial_sum(local_sizes.begin(), local_sizes.end(), &local_starts[1]);
    n = local_starts[p];
  }

  // To do maybe: enter local size in each process and gather in constructor (much handier)
  // template<typename LinearProcessGroup>
  // explicit uneven_block(const LinearProcessGroup& pg, std::size_t my_local_size) 

  // If there are n elements in the distributed data structure, returns the number of elements stored locally.
  template<typename SizeType>
  SizeType block_size(SizeType) const
  { return local_sizes[id]; }

  // If there are n elements in the distributed data structure, returns the number of elements stored on processor ID
  template<typename SizeType, typename ProcessID>
  SizeType block_size(ProcessID id, SizeType) const
  { return local_sizes[id]; }

  // Returns the processor on which element with global index i is stored
  template<typename SizeType>
  SizeType operator()(SizeType i) const
  {
    BOOST_ASSERT (i >= (SizeType) 0 && i < (SizeType) n); // check for valid range
    size_vector::const_iterator lb = std::lower_bound(local_starts.begin(), local_starts.end(), (std::size_t) i);
    return ((SizeType)(*lb) == i ? lb : --lb) - local_starts.begin();
  }

  // Find the starting index for processor with the given id
  template<typename ID>
  std::size_t start(ID id) const 
  {
    return local_starts[id];
  }

  // Find the local index for the ith global element
  template<typename SizeType>
  SizeType local(SizeType i) const
  { 
    SizeType owner = (*this)(i);
    return i - start(owner);
  }

  // Returns the global index of local element i
  template<typename SizeType>
  SizeType global(SizeType i) const
  { return global(id, i); }

  // Returns the global index of the ith local element on processor id
  template<typename ProcessID, typename SizeType>
  SizeType global(ProcessID id, SizeType i) const
  { return i + start(id); }

 private:
  std::size_t              id;           //< The ID number of this processor
  std::size_t              p;            //< The number of processors
  std::size_t              n;            //< The size of the problem space
  std::vector<std::size_t> local_sizes;  //< The sizes of all blocks
  std::vector<std::size_t> local_starts; //< Lowest global index of each block
};


struct oned_block_cyclic
{
  template<typename LinearProcessGroup>
  explicit oned_block_cyclic(const LinearProcessGroup& pg, std::size_t size)
    : id(process_id(pg)), p(num_processes(pg)), size(size) { }
      
  template<typename SizeType>
  SizeType block_size(SizeType n) const
  { 
    return block_size(id, n);
  }

  template<typename SizeType, typename ProcessID>
  SizeType block_size(ProcessID id, SizeType n) const
  {
    SizeType all_blocks = n / size;
    SizeType extra_elements = n % size;
    SizeType everyone_gets = all_blocks / p;
    SizeType extra_blocks = all_blocks % p;
    SizeType my_blocks = everyone_gets + (p < extra_blocks? 1 : 0);
    SizeType my_elements = my_blocks * size 
                         + (p == extra_blocks? extra_elements : 0);
    return my_elements;
  }

  template<typename SizeType>
  SizeType operator()(SizeType i) const
  { 
    return (i / size) % p;
  }

  template<typename SizeType>
  SizeType local(SizeType i) const
  { 
    return ((i / size) / p) * size + i % size;
  }

  template<typename SizeType>
  SizeType global(SizeType i) const
  { return global(id, i); }

  template<typename ProcessID, typename SizeType>
  SizeType global(ProcessID id, SizeType i) const
  { 
    return ((i / size) * p + id) * size + i % size;
  }

 private:
  std::size_t id;                   //< The ID number of this processor
  std::size_t p;                    //< The number of processors
  std::size_t size;                 //< Block size
};

struct twod_block_cyclic
{
  template<typename LinearProcessGroup>
  explicit twod_block_cyclic(const LinearProcessGroup& pg,
                             std::size_t block_rows, std::size_t block_columns,
                             std::size_t data_columns_per_row)
    : id(process_id(pg)), p(num_processes(pg)), 
      block_rows(block_rows), block_columns(block_columns), 
      data_columns_per_row(data_columns_per_row)
  { }
      
  template<typename SizeType>
  SizeType block_size(SizeType n) const
  { 
    return block_size(id, n);
  }

  template<typename SizeType, typename ProcessID>
  SizeType block_size(ProcessID id, SizeType n) const
  {
    // TBD: This is really lame :)
    int result = -1;
    while (n > 0) {
      --n;
      if ((*this)(n) == id && (int)local(n) > result) result = local(n);
    }
    ++result;

    //    std::cerr << "Block size of id " << id << " is " << result << std::endl;
    return result;
  }

  template<typename SizeType>
  SizeType operator()(SizeType i) const
  { 
    SizeType result = get_block_num(i) % p;
    //    std::cerr << "Item " << i << " goes on processor " << result << std::endl;
    return result;
  }

  template<typename SizeType>
  SizeType local(SizeType i) const
  { 
    // Compute the start of the block
    std::size_t block_num = get_block_num(i);
    //    std::cerr << "Item " << i << " is in block #" << block_num << std::endl;

    std::size_t local_block_num = block_num / p;
    std::size_t block_start = local_block_num * block_rows * block_columns;

    // Compute the offset into the block 
    std::size_t data_row = i / data_columns_per_row;
    std::size_t data_col = i % data_columns_per_row;
    std::size_t block_offset = (data_row % block_rows) * block_columns 
                             + (data_col % block_columns);    

    //    std::cerr << "Item " << i << " maps to local index " << block_start+block_offset << std::endl;
    return block_start + block_offset;
  }

  template<typename SizeType>
  SizeType global(SizeType i) const
  { 
    // Compute the (global) block in which this element resides
    SizeType local_block_num = i / (block_rows * block_columns);
    SizeType block_offset = i % (block_rows * block_columns);
    SizeType block_num = local_block_num * p + id;

    // Compute the position of the start of the block (globally)
    SizeType block_start = block_num * block_rows * block_columns;

    std::cerr << "Block " << block_num << " starts at index " << block_start
              << std::endl;

    // Compute the row and column of this block
    SizeType block_row = block_num / (data_columns_per_row / block_columns);
    SizeType block_col = block_num % (data_columns_per_row / block_columns);

    SizeType row_in_block = block_offset / block_columns;
    SizeType col_in_block = block_offset % block_columns;

    std::cerr << "Local index " << i << " is in block at row " << block_row
              << ", column " << block_col << ", in-block row " << row_in_block
              << ", in-block col " << col_in_block << std::endl;

    SizeType result = block_row * block_rows + block_col * block_columns
                    + row_in_block * block_rows + col_in_block;


    std::cerr << "global(" << i << "@" << id << ") = " << result 
              << " =? " << local(result) << std::endl;
    BOOST_ASSERT(i == local(result));
    return result;
  }

 private:
  template<typename SizeType>
  std::size_t get_block_num(SizeType i) const
  {
    std::size_t data_row = i / data_columns_per_row;
    std::size_t data_col = i % data_columns_per_row;
    std::size_t block_row = data_row / block_rows;
    std::size_t block_col = data_col / block_columns;
    std::size_t blocks_in_row = data_columns_per_row / block_columns;
    std::size_t block_num = block_col * blocks_in_row + block_row;
    return block_num;
  }

  std::size_t id;                   //< The ID number of this processor
  std::size_t p;                    //< The number of processors
  std::size_t block_rows;           //< The # of rows in each block
  std::size_t block_columns;        //< The # of columns in each block
  std::size_t data_columns_per_row; //< The # of columns per row of data
};

class twod_random
{
  template<typename RandomNumberGen>
  struct random_int
  {
    explicit random_int(RandomNumberGen& gen) : gen(gen) { }

    template<typename T>
    T operator()(T n) const
    {
      uniform_int<T> distrib(0, n-1);
      return distrib(gen);
    }

  private:
    RandomNumberGen& gen;
  };
  
 public:
  template<typename LinearProcessGroup, typename RandomNumberGen>
  explicit twod_random(const LinearProcessGroup& pg,
                       std::size_t block_rows, std::size_t block_columns,
                       std::size_t data_columns_per_row,
                       std::size_t n,
                       RandomNumberGen& gen)
    : id(process_id(pg)), p(num_processes(pg)), 
      block_rows(block_rows), block_columns(block_columns), 
      data_columns_per_row(data_columns_per_row),
      global_to_local(n / (block_rows * block_columns))
  { 
    std::copy(make_counting_iterator(std::size_t(0)),
              make_counting_iterator(global_to_local.size()),
              global_to_local.begin());

#if defined(BOOST_NO_CXX98_RANDOM_SHUFFLE)
    std::shuffle(global_to_local.begin(), global_to_local.end(), gen);
#else
    random_int<RandomNumberGen> rand(gen);
    std::random_shuffle(global_to_local.begin(), global_to_local.end(), rand);
#endif
  }
      
  template<typename SizeType>
  SizeType block_size(SizeType n) const
  { 
    return block_size(id, n);
  }

  template<typename SizeType, typename ProcessID>
  SizeType block_size(ProcessID id, SizeType n) const
  {
    // TBD: This is really lame :)
    int result = -1;
    while (n > 0) {
      --n;
      if ((*this)(n) == id && (int)local(n) > result) result = local(n);
    }
    ++result;

    //    std::cerr << "Block size of id " << id << " is " << result << std::endl;
    return result;
  }

  template<typename SizeType>
  SizeType operator()(SizeType i) const
  { 
    SizeType result = get_block_num(i) % p;
    //    std::cerr << "Item " << i << " goes on processor " << result << std::endl;
    return result;
  }

  template<typename SizeType>
  SizeType local(SizeType i) const
  { 
    // Compute the start of the block
    std::size_t block_num = get_block_num(i);
    //    std::cerr << "Item " << i << " is in block #" << block_num << std::endl;

    std::size_t local_block_num = block_num / p;
    std::size_t block_start = local_block_num * block_rows * block_columns;

    // Compute the offset into the block 
    std::size_t data_row = i / data_columns_per_row;
    std::size_t data_col = i % data_columns_per_row;
    std::size_t block_offset = (data_row % block_rows) * block_columns 
                             + (data_col % block_columns);    

    //    std::cerr << "Item " << i << " maps to local index " << block_start+block_offset << std::endl;
    return block_start + block_offset;
  }

 private:
  template<typename SizeType>
  std::size_t get_block_num(SizeType i) const
  {
    std::size_t data_row = i / data_columns_per_row;
    std::size_t data_col = i % data_columns_per_row;
    std::size_t block_row = data_row / block_rows;
    std::size_t block_col = data_col / block_columns;
    std::size_t blocks_in_row = data_columns_per_row / block_columns;
    std::size_t block_num = block_col * blocks_in_row + block_row;
    return global_to_local[block_num];
  }

  std::size_t id;                   //< The ID number of this processor
  std::size_t p;                    //< The number of processors
  std::size_t block_rows;           //< The # of rows in each block
  std::size_t block_columns;        //< The # of columns in each block
  std::size_t data_columns_per_row; //< The # of columns per row of data
  std::vector<std::size_t> global_to_local;
};

class random_distribution
{
  template<typename RandomNumberGen>
  struct random_int
  {
    explicit random_int(RandomNumberGen& gen) : gen(gen) { }

    template<typename T>
    T operator()(T n) const
    {
      uniform_int<T> distrib(0, n-1);
      return distrib(gen);
    }

  private:
    RandomNumberGen& gen;
  };
  
 public:
  template<typename LinearProcessGroup, typename RandomNumberGen>
  random_distribution(const LinearProcessGroup& pg, RandomNumberGen& gen,
                      std::size_t n)
    : base(pg, n), local_to_global(n), global_to_local(n)
  {
    std::copy(make_counting_iterator(std::size_t(0)),
              make_counting_iterator(n),
              local_to_global.begin());

#if defined(BOOST_NO_CXX98_RANDOM_SHUFFLE)
    std::shuffle(local_to_global.begin(), local_to_global.end(), gen);
#else
    random_int<RandomNumberGen> rand(gen);
    std::random_shuffle(local_to_global.begin(), local_to_global.end(), rand);
#endif

    for (std::vector<std::size_t>::size_type i = 0; i < n; ++i)
      global_to_local[local_to_global[i]] = i;
  }

  template<typename SizeType>
  SizeType block_size(SizeType n) const
  { return base.block_size(n); }

  template<typename SizeType, typename ProcessID>
  SizeType block_size(ProcessID id, SizeType n) const
  { return base.block_size(id, n); }

  template<typename SizeType>
  SizeType operator()(SizeType i) const
  {
    return base(global_to_local[i]);
  }

  template<typename SizeType>
  SizeType local(SizeType i) const
  { 
    return base.local(global_to_local[i]);
  }

  template<typename ProcessID, typename SizeType>
  SizeType global(ProcessID p, SizeType i) const
  { 
    return local_to_global[base.global(p, i)];
  }

  template<typename SizeType>
  SizeType global(SizeType i) const
  { 
    return local_to_global[base.global(i)];
  }

 private:
  block base;
  std::vector<std::size_t> local_to_global;
  std::vector<std::size_t> global_to_local;
};

} } // end namespace boost::parallel

#endif // BOOST_PARALLEL_DISTRIBUTION_HPP


/* distribution.hpp
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
*/