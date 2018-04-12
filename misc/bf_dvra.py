#Bellman-Ford distance vector routing algorithm
#to find the routing table of a particular node
#given incoming distance vectors to that node
#and costs of the corresponding links

given = ['B', 'D', 'E']
nodes = ['A', 'B', 'C', 'D', 'E', 'F']
b_vector = [6, 0, 8, 12, 6, 2]
d_vector = [4, 12, 6, 0, 9, 10]
e_vector = [1, 6, 3, 9, 0, 4]
vectors = [b_vector, d_vector, e_vector]

b_cost = 4
d_cost = 3
e_cost = 5
costs = [b_cost, d_cost, e_cost]

dist = [100, 100, 100, 100, 100, 100]
to = []
via = [0, 0, 0, 0, 0, 0]

for i in range(6):
	if i==2:
		continue
	to.append(i)
	for j in range(3):
		d = vectors[j][i] + costs[j]
		if d < dist[i]:
			dist[i] = d
			via[i] = j

print '\nRouting Table of node C\n'
print ' --------------------------'
print ' |  TO   |  VIA  |DISTANCE|'
print ' --------------------------'
for i in range(6):
	if i==2:
		continue
	print ' |   '+nodes[i]+'   |   '+given[via[i]]+'   |   '+str(dist[i])+'    |'
	print ' --------------------------'
print


