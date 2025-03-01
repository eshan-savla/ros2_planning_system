
#pragma once

#include "plansys2_msgs/msg/node.hpp"
#include "plansys2_msgs/msg/tree.hpp"

#include "plansys2_pddl_parser/ParamCond.h"

namespace parser { namespace pddl {

class Imply : public ParamCond {

public:
	Condition * cond_1; // The initial condition of imply
	Condition * cond_2; // The latter condition of imply

	Imply()
		: cond_1( 0 ), cond_2( 0 ) {}

	Imply( const Imply * f, Domain & d )
		: ParamCond( f ), cond_1( 0 ), cond_2( 0 ) {
		if ( f->cond_1 ) cond_1 = f->cond_1->copy( d );
		if ( f->cond_2 ) cond_2 = f->cond_2->copy( d );
	}

	~Imply() {
		if ( cond_1 ) delete cond_1; // bc new creation
		if ( cond_2 ) delete cond_2;
	}

	void print( std::ostream & s ) const {
		s << "Imply" << params << ":\n";
		if ( cond_1 ) cond_1->print( s );
		if( cond_2 ) cond_2->print( s );
	}

	void PDDLPrint( std::ostream & s, unsigned indent, const TokenStruct< std::string > & ts, const Domain & d ) const override;

	plansys2_msgs::msg::Node::SharedPtr getTree( plansys2_msgs::msg::Tree & tree, const Domain & d, const std::vector<std::string> & replace = {}, const std::map<std::string, std::vector<std::string>> & instances_map = {} ) const override;

	void parse( Stringreader & f, TokenStruct< std::string > & ts, Domain & d );

	void addParams( int m, unsigned n ) {
		cond_1->addParams( m, n );
		cond_2->addParams( m, n );
	}

	Condition * copy( Domain & d ) {
		return new Imply( this, d );
	}

};

} } // namespaces
