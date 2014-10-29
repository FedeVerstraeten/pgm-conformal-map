#include "common.hpp"
#include "binTree.hpp"
#include <string>

int main(void)
{
	binTree<string> t1("+"),t2("5"),t3("*"),t4(t2),t5("z");
	t1.insert(t2);
	t1.insert(t3);

	t3.insert(t4);
	t3.insert(t5);

	t1.printTree(cout);

    return 0;
}
