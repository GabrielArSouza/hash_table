#include <iostream>
#include <string>
#include <utility>
#include <tuple>

#include "hashtable.h"

using AcctKey = std::tuple< std::string, int , int , int >;

struct Account 
{
	std::string name; //<! Nome
	int bank;		  //<! Código do banco
	int branch;		  //<! Agência da conta
	int account;	  //<! Número da conta
	float balance;	  //<! Saldo da conta
	AcctKey key;	  //<! Chave da conta

	/**
	 * @brief      Constutor
	 *
	 * @param[in]  n     Nome do usuário da conta
	 * @param[in]  b     Codigo do banco
	 * @param[in]  bn    Agência da conta
	 * @param[in]  ac    Número da conta
	 * @param[in]  blc   Dinheiro da conta
	 */
	Account( std::string n, int b, int bn,
			 int ac, float blc )
			: name ( n )
			, bank ( b )
			, branch ( bn )
			, account ( ac )
			, balance ( bn )
			, key (n, b, bn, ac)
	{ /*empty*/ }

	/**
	 * @brief      Pega a chave da conta
	 *
	 * @return     A chave da conta.
	 */
	AcctKey get_key() const
	{
		return key;
	} 
};

/**
 * @brief      Função de hash primária
 */
struct KeyHash 
{
	std::size_t operator()( const AcctKey & k_ ) const
	{
		auto name = std::get<0>(k_);
		auto bank = std::get<1>(k_);
		auto bran = std::get<2>(k_);
		auto acco = std::get<3>(k_);

		std::hash<std::string> hash_str;
		std::hash< int > hash_int;

		return ( (hash_str(name)) xor (hash_int(bank)) xor
				 (hash_int(bran)) xor (hash_int(acco)));
	}
};

/**
 * @brief      Compara se duas chaves são iguais
 */
struct KeyEqual
{
	bool
	operator()( const AcctKey & rhs_, 
				const AcctKey & lhs_ ) const
	{
		return rhs_ == lhs_;
	}
};

int main ()
{
	HashTbl<AcctKey, Account, KeyHash, KeyEqual> tb;
	
	//<! Criando dados. 
	Account a = {"Alex Bastos", 1, 1668, 54321, 1500.00 };
	Account b = {"Aline Souza", 1, 1668, 45794, 530.00};
	Account c = {"Cristiano Ronaldo", 13, 557, 87629, 150000.00};
	Account d = {"Jose Lima", 18, 331, 1231, 850.00};
	Account e = {"Saulo Cunha", 116, 666, 84312, 5490.00};

	tb.insert(a.get_key(), a);
	tb.insert(b.get_key(), b);
	tb.insert(c.get_key(), c);
	tb.insert(d.get_key(), d);
	tb.insert(e.get_key(), e);
	
	tb.print();

	tb.remove(d.get_key());

	tb.print();
	
	tb.remove(d.get_key());
	
	return 0;

}