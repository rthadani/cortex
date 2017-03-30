#ifndef TENSOR_OPERATIONS_H
#define TENSOR_OPERATIONS_H


namespace tensor { namespace operations {
    struct operation_type
    {
      enum _enum
      {
	add = 0,
	subtract,
	multiply,
	divide,
      };
    };

    struct general_operation
    {
      int op_type;
      bool reverse_operands;
      __device__ general_operation( int op, bool rev_ops = false )
	: op_type(op)
	, reverse_operands(rev_ops){}
      template<typename dtype>
      __device__ dtype operator()( dtype lhs, dtype rhs ) const {
	switch( op_type ) {
	case operation_type::add:
	  return  lhs + rhs;
	case operation_type::subtract:
	  return reverse_operands ? rhs - lhs : lhs - rhs;
	case operation_type::multiply:
	  return lhs * rhs;
	case operation_type::divide:
	  return reverse_operands ? rhs / lhs : lhs / rhs;
	};
	return (dtype) 0;
      }
    };
  }}


#define EXPLODE_OP_SYSTEM(varname)		\
  int op_type##varname


#define ENCAPSULATE_OP_SYSTEM(varname)		\
  general_operation(op_type##varname)

#define EXPLODE_OP_SYSTEM_REV(varname)		\
  int op_type##varname, int rev_op##varname

#define ENCAPSULATE_OP_SYSTEM_REV(varname)		\
  general_operation(op_type##varname, (bool)rev_op##varname)

#endif
