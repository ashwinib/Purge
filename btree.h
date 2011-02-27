using namespace std;
class TreeNode
	{
	public:
		string entry;
		int color;
		TreeNode *parent;
		TreeNode *left;
		TreeNode *right;	
	};
extern TreeNode *root , *nil;
TreeNode *insertinRB(TreeNode *);
void initRB();


