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