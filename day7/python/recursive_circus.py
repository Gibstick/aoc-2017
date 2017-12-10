import fileinput
import re

from typing import Dict, Set, Sequence, Tuple, Union


input_regex = re.compile(r"([a-z]+) \(([0-9]+)\)( -> )?(.*)")
comma_list_regex = re.compile(r", ")


def parse_input_line(line: str) -> Tuple[str, int, Sequence[str]]:
    """Takes a line of input and returns a 3-tuple
    of program name, weight, and list of children"""
    match = input_regex.match(line)
    if match[4]:
        children = comma_list_regex.split(match[4])
    else:
        children = ()
    return (match[1], int(match[2]), children)


nodes: Dict[str, Sequence[str]] = {}
node_weights: Dict[str, int] = {}

parented_nodes: Set[str] = set()
orphan_nodes: Set[str] = set()

for line in fileinput.input():
    name, weight, children = parse_input_line(line)
    # print("{}, {}, {}".format(name, weight, children))
    nodes[name] = children
    node_weights[name] = weight

    # all children of current node are not orphans
    for child in children:
        if child in orphan_nodes:
            orphan_nodes.remove(child)

        # print("adding {} as non-orphan".format(child))
        assert(child not in parented_nodes)
        parented_nodes.add(child)

    if name not in parented_nodes:
        # print("added {} as orphan".format(name))
        orphan_nodes.add(name)

assert(len(orphan_nodes) == 1)
root_node = orphan_nodes.pop()
print("Root node: %s" % root_node)


# recursively find and store weights
def find_subtree_weight(
    node: str,
    nodes: Dict[str, Sequence[str]],
    subtree_weights: Dict[str, int]
) -> int:
    children = nodes[node]
    if not children:
        return subtree_weights[node]
    else:
        weight = subtree_weights[node]
        for child in children:
            weight += find_subtree_weight(child, nodes, subtree_weights)

        assert(weight >= subtree_weights[child])
        subtree_weights[node] = weight
        return weight


subtree_weights = dict(node_weights)
find_subtree_weight(root_node, nodes, subtree_weights)


# go through tree again and find lowest unbalanced node
def find_unbalanced(
    node: str,
    nodes: Dict[str, Sequence[str]],
    subtree_weights: Dict[str, int],
    target_weight: int = 0
) -> Union[Tuple[str, int], None]:
    children = nodes[node]

    if not children:
        return None  # this shouldn't happen
    elif len(children) == 1:
        # print("only one child: %s" % children[0])
        # can we even have this condition?
        return find_unbalanced(
            children[0],
            nodes,
            subtree_weights,
            0  # TODO: does this even make sense?
        )
    else:  # length of list is at least 2 here
        # UGLY HACK
        weights = [subtree_weights[child] for child in children]
        first_weight = weights[0]
        part_a = [weight for weight in enumerate(weights) if weight[1] == first_weight]
        part_b = [weight for weight in enumerate(weights) if weight[1] != first_weight]
        # print("Examining node {} with children {}".format(node, children))
        # print("parts:\n{}\n{}".format(part_a, part_b))

        # we are guaranteed to have exactly one program is the wrong weight
        # so we can take the list of length one as the unbalanced subtree
        if len(part_a) == 1:
            unbalanced_node = children[part_a[0][0]]
            target = part_b[0][1]
        elif len(part_b) == 1:
            unbalanced_node = children[part_b[0][0]]
            target = part_a[0][1]
        elif len(part_a) == len(children) or len(part_b) == len(children):
            # print("found unbalanced node: %s" % node)
            # print(part_a)
            # print(part_b)

            return (node, target_weight)
        else:
            assert(not "This shouldn't get here!")

        # print("")

        return find_unbalanced(
            unbalanced_node,
            nodes,
            subtree_weights,
            target
        )


unbalanced_node, target_weight = find_unbalanced(
    root_node, nodes, subtree_weights
)

weight_diff = subtree_weights[unbalanced_node] - target_weight
needed_weight = node_weights[unbalanced_node] - weight_diff

print("Unbalanced node: %s, %s" % (unbalanced_node, needed_weight))
