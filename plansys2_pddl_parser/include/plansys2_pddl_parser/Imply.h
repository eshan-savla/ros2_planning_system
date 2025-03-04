
#pragma once

#include "plansys2_msgs/msg/node.hpp"
#include "plansys2_msgs/msg/tree.hpp"

#include "plansys2_pddl_parser/ParamCond.h"

namespace parser { namespace pddl {

class Imply : public ParamCond {

public:
	Condition * left; // The initial condition of imply
	Condition * right; // The latter condition of imply

	Imply()
		: left( 0 ), right( 0 ) {}

	Imply( const Imply * f, Domain & d )
		: ParamCond( f ), left( 0 ), right( 0 ) {
		if ( f->left ) left = f->left->copy( d );
		if ( f->right ) right = f->right->copy( d );
	}

	~Imply() {
		if ( left ) delete left; // bc new creation
		if ( right ) delete right;
	}

	void print( std::ostream & s ) const {
		s << "Imply" << params << ":\n";
		if ( left ) left->print( s );
		if( right ) right->print( s );
	}

	void PDDLPrint( std::ostream & s, unsigned indent, const TokenStruct< std::string > & ts, const Domain & d ) const override;

	plansys2_msgs::msg::Node::SharedPtr getTree( plansys2_msgs::msg::Tree & tree, const Domain & d, const std::vector<std::string> & replace = {}, const std::map<std::string, std::vector<std::string>> & instances_map = {} ) const override;

	void parse( Stringreader & f, TokenStruct< std::string > & ts, Domain & d );

	void addParams( int m, unsigned n ) {
		left->addParams( m, n );
		right->addParams( m, n );
	}

	Condition * copy( Domain & d ) {
		return new Imply( this, d );
	}

};

} } // namespaces
