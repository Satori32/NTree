#include <iostream>
#include <memory>
#include <vector>
#include <tuple>

//debug is incomplete.


template<class T>
class NTree {
public:
	NTree() {
		Root = std::make_shared<Node>();
		Pointer = Root;
	}
	NTree(const T& In) {
		Root = std::make_shared<Node>({ In,Root,{} });
		Pointer = Root;
	}

	bool MoveParent() {
		if (Pointer == nullptr) { return false; }
		if (Pointer->Parent == nullptr) { return false; }
		Pointer = Pointer->Parent;

		return true;
	}
	bool MoveChild(std::size_t P) {
		if (Pointer == nullptr) { return false; }

		if (Pointer->Nodes.size() <= P) { return false; }

		Pointer = Pointer->Nodes[P];
		return true;
	}
	std::size_t GetChildCount() {
		if (Pointer == nullptr) { return 0; }
		return Pointer->Nodes.size();
	}
	bool PushChild(const T& In) {
		if (Pointer == nullptr) { return false; }
		typename Node::SharedNode X = std::make_shared<Node>();
		X->Value = In;
		X->Parent = Pointer;
		Pointer->Nodes.push_back(X);
		//Pointer->Nodes.push_back({  In,Pointer,{} });
		return true;
	}
	bool PopChild(std::size_t P) {
		if (Pointer == nullptr) { return false; }

		if (Pointer->Nodes.size() <= P) { return false; }

		Pointer->Nodes.erase(Pointer->Nodes.begin() + P);
		return true;
	}

	const std::tuple<bool,T&> GetValue() {
		return { Pointer != nullptr,Pointer->Value };
	}

	bool SetValue(const T& In) {
		if (Pointer == nullptr) { return false; }

		Pointer->Value = In;
		return true;
	}


	bool MoveRoot() {
		if (Root == nullptr) { return false; }
		Pointer = Root;
		return true;
	}

protected:	
	struct Node {
	public:
		typedef std::shared_ptr<Node> SharedNode;
		T Value;
		SharedNode Parent=nullptr;
		std::vector<SharedNode> Nodes;
	};

	typename Node::SharedNode Root;// = std::make_shared<Node>();
	typename Node::SharedNode Pointer;// = Root;
};

int main() {
	NTree<int> T;

	T.SetValue(10);

	std::cout << std::get<1>(T.GetValue()) << std::endl;

	T.PushChild(8);
	T.MoveChild(0);
	std::cout << std::get<1>(T.GetValue()) << std::endl;
	T.MoveParent();
	std::cout << T.GetChildCount() << std::endl;
	T.PopChild(0);

	std::cout << T.GetChildCount() << std::endl;
	
	return 0;
}