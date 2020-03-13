int printElements(Cvor);
int printLevel(Cvor, int, int);
int getLevelCount(Cvor);

int getLevelCount(Cvor root)
{
	if (!root)
		return 0;

	int rightCount = 1 + getLevelCount(root->right);
	int leftCount = 1 + getLevelCount(root->left);

	if (leftCount < rightCount)
		return rightCount;
	else
		return leftCount;
}
int printLevel(Cvor root, int level, int i)
{
	if (!root)
		return 0;
	else if (root && level == 0) {
		printf("Level: %d %d\n", i + 1, root->broj);
		return 1;
	}
	else {
		printLevel(root->left, level - 1, i);
		printLevel(root->right, level - 1, i);
		return 1;
	}
}
int printElements(Cvor root)
{
	int height = getLevelCount(root);
	int i = 0;

	for (i = 0; i < height; i++) {
		printLevel(root, i, i);
	}

	return 1;
}
