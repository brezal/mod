#ifndef MOD_GRAPH_H
#define MOD_GRAPH_H

#include <mod/Config.h>

#include <iosfwd>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace mod {
template<typename Sig> struct Function;
struct GraphPrinter;
namespace lib {
namespace Graph {
struct Single;
} // namespace Graph
} // namespace lib

// rst-class: Graph
// rst:
// rst:		This class models an undirected graph with labels on vertices and edges,
// rst:		without loops and without parallel edges.
// rst:		Certain labels are regarded as models of chemical atoms and bonds.
// rst:		See :ref:`mol-enc` for more information on this.
// rst:		See also :ref:`cpp-GraphGraphInterface` for the documentation for the
// rst:		graph interface for this class.
// rst:
// rst-class-start:

struct Graph {
	class Vertex;
	class Edge;
	class VertexIterator;
	class VertexRange;
	class EdgeIterator;
	class EdgeRange;
	class IncidentEdgeIterator;
	class IncidentEdgeRange;
private: // The actual class interface
	Graph(std::unique_ptr<lib::Graph::Single> g);
	Graph(const Graph&) = delete;
	Graph &operator=(const Graph&) = delete;
public:
	~Graph();
	// rst: .. function:: std::size_t getId() const
	// rst:
	// rst:		:returns: the unique instance id among :class:`Graph` objects.
	std::size_t getId() const;
	friend std::ostream &operator<<(std::ostream &s, const mod::Graph &g);
	lib::Graph::Single &getGraph() const;
public: // graph interface
	// rst: .. function:: std::size_t numVertices() const
	// rst:
	// rst:		:returns: the number of vertices in the graph.
	std::size_t numVertices() const;
	// rst: .. function:: VertexRange vertices() const
	// rst:
	// rst:		:returns: a range of all vertices in the graph.
	VertexRange vertices() const;
	// rst: .. function:: std::size_t numEdges() const
	// rst:
	// rst:		:returns: the number of edges in the graph.
	std::size_t numEdges() const;
	// rst: .. function:: EdgeRange edges() const
	// rst:
	// rst:		:returns: a range of all edges in the graph.
	EdgeRange edges() const;
public:
	// rst: .. function:: std::pair<std::string, std::string> print() const
	// rst:               std::pair<std::string, std::string> print(const GraphPrinter &first, const GraphPrinter &second) const
	// rst:
	// rst:		Print the graph, using either the default options or the options in ``first`` and ``second``.
	// rst:		If ``first`` and ``second`` are the same, only one depiction will be made.
	// rst:
	// rst:		:returns: a pair of names for the PDF-files that will be compiled in post-processing.
	// rst:			If ``first`` and ``second`` are the same, the two file prefixes are equal.
	std::pair<std::string, std::string> print() const;
	std::pair<std::string, std::string> print(const GraphPrinter &first, const GraphPrinter &second) const;
	// rst: .. function:: std::string getGMLString(bool withCoords = false) const
	// rst:
	// rst:		:returns: the :ref:`GML <graph-gml>` representation of the graph,
	// rst:		          optionally with generated 2D coordinates.
	// rst:		:throws: :any:`LogicError` when coordinates are requested, but
	// rst:		         none can be generated.
	std::string getGMLString(bool withCoords = false) const;
	// rst: .. function:: std::string printGML(bool withCoords = false) const
	// rst:
	// rst:		Print the :ref:`GML <graph-gml>` representation of the graph,
	// rst:		optionally with generated 2D coordinates.
	// rst:
	// rst:		:returns: the filename of the printed GML file.
	// rst:		:throws: :any:`LogicError` when coordinates are requested, but
	// rst:		         none can be generated.
	std::string printGML(bool withCoords = false) const;
	// rst: .. function:: const std::string &getName() const
	// rst:               void setName(std::string name) const
	// rst:
	// rst:		Access the name of the graph.
	const std::string &getName() const;
	void setName(std::string name) const;
	// rst: .. function:: const std::string &getSmiles() const
	// rst:
	// rst:		:returns: the canonical :ref:`SMILES string <graph-smiles>` of the graph, if it's a molecule.
	// rst:		:throws: :any:`LogicError` if the graph is not a molecule.
	const std::string &getSmiles() const;
	// rst: .. function:: const std::string &getGraphDFS() const
	// rst:
	// rst:		:returns: the :ref:`GraphDFS <graph-graphDFS>` string of the graph.
	const std::string &getGraphDFS() const;
	// rst: .. function:: const std::string &getLinearEncoding() const
	// rst:
	// rst:		:returns: the :ref:`SMILES <graph-smiles>` string if the graph is a molecule, otherwise the :ref:`GraphDFS <graph-graphDFS>` string.
	const std::string &getLinearEncoding() const;
	// rst: .. function:: bool getIsMolecule() const
	// rst:
	// rst:		:returns: whether or not the graph models a molecule. See :ref:`mol-enc`.
	bool getIsMolecule() const;
	// rst: .. function:: double getEnergy() const
	// rst:
	// rst:		:returns: some energy value if the graph is a molecule.
	// rst:			The energy is calculated using Open Babel, unless already calculated or cached by :cpp:func:`Graph::cacheEnergy`.
	double getEnergy() const;
	// rst: .. function:: void cacheEnergy(double value) const
	// rst:
	// rst:		If the graph models a molecule, sets the energy to a given value.
	// rst:
	// rst:		:throws: :class:`LogicError` if the graph is not a molecule.
	void cacheEnergy(double value) const;
	// rst: .. function:: double getMolarMass() const
	// rst:
	// rst:		:returns: the molar mass of the graph, if it is a molecule.
	// rst:			The molar mass is calculated by Open Babel.
	double getMolarMass() const;
	// rst: .. function:: unsigned int vLabelCount(const std::string &label) const
	// rst:
	// rst:		:returns: the number of vertices in the graph with the given label.
	unsigned int vLabelCount(const std::string &label) const;
	// rst: .. function:: unsigned int eLabelCount(const std::string &label) const
	// rst:
	// rst:		:returns: the number of edges in the graph with the given label.
	unsigned int eLabelCount(const std::string &label) const;
	// rst: .. function:: std::size_t isomorphism(std::shared_ptr<Graph> g, std::size_t maxNumMatches) const
	// rst:
	// rst:		:returns: the number of isomorphisms found from this graph to ``g``, but at most ``maxNumMatches``.
	std::size_t isomorphism(std::shared_ptr<Graph> g, std::size_t maxNumMatches) const;
	// rst: .. function:: std::size_t monomorphism(std::shared_ptr<Graph> g, std::size_t maxNumMatches) const
	// rst:
	// rst:		:returns: the number of monomorphisms from this graph to ``g``, though at most ``maxNumMatches``.
	std::size_t monomorphism(std::shared_ptr<Graph> g, std::size_t maxNumMatches) const;
	// rst: .. function:: std::shared_ptr<Graph> makePermutation() const
	// rst:
	// rst:		:returns: a graph isomorphic to this, but with the vertex indices randomly permuted.
	std::shared_ptr<Graph> makePermutation() const;
	// rst: .. function:: void setImage(std::shared_ptr<Function<std::string()> > image)
	// rst:
	// rst:		Set a custom depiction for the graph. The depiction file used will be the string
	// rst:		returned by the given function, with ``.pdf`` appended.
	// rst:		The function will only be called once.
	// rst:		Give ``nullptr`` to use auto-generated depiction.
	void setImage(std::shared_ptr<Function<std::string()> > image);
	// rst: .. function:: std::shared_ptr<Function<std::string()> > getImage() const
	// rst:
	// rst:		:returns: the current custom depiction file function.
	std::shared_ptr<Function<std::string()> > getImage() const;
	// rst: .. function:: void setImageCommand(std::string cmd)
	// rst:
	// rst:		Set a command to be run in post-processing if a custom depiction is set.
	// rst:		The command is only run once.
	void setImageCommand(std::string cmd);
	// rst: .. function:: std::string getImageCommand() const
	// rst:
	// rst:		:returns: the current post-processing command.
	std::string getImageCommand() const;
	// rst: .. function:: Vertex getVertexFromExternalId(int id) const
	// rst:
	// rst:		If the graph was not loaded from an external data format, then this function
	// rst:		always return a null descriptor.
	// rst:		If the graph was loaded from a SMILES string, but *any* class label was not unique,
	// rst:		then the function always return a null descriptor.
	// rst:
	// rst:		.. note:: In general there is no correlation between external and internal ids.
	// rst:
	// rst:		:returns: the vertex descriptor for the given external id.
	// rst:		          The descriptor is null if the external id was not used.
	Vertex getVertexFromExternalId(int id) const;
private:
	struct Pimpl;
	std::unique_ptr<Pimpl> p;
public:
	// rst: .. function:: static std::shared_ptr<Graph> graphGMLString(const std::string &data)
	// rst:
	// rst:		:returns: a graph created from the given :ref:`GML <graph-gml>` data.
	// rst:		:throws: :class:`InputError` on bad input.
	static std::shared_ptr<Graph> graphGMLString(const std::string &data);
	// rst: .. function:: static std::shared_ptr<Graph> graphGML(const std::string &file)
	// rst:
	// rst:		:returns: a graph loaded from the given :ref:`GML <graph-gml>` file.
	// rst:		:throws: :class:`InputError` on bad input.
	static std::shared_ptr<Graph> graphGML(const std::string &file);
	// rst: .. function:: static std::shared_ptr<Graph> graphDFS(const std::string &graphDFS)
	// rst:
	// rst:		:returns: a graph loaded from the given :ref:`GraphDFS <graph-graphDFS>` string.
	// rst:		:throws: :class:`InputError` on bad input.
	static std::shared_ptr<Graph> graphDFS(const std::string &graphDFS);
	// rst: .. function:: static std::shared_ptr<Graph> smiles(const std::string &smiles)
	// rst:
	// rst:		:returns: a graph representing a molecule, loaded from the given :ref:`SMILES <graph-smiles>` string.
	// rst:		:throws: :class:`InputError` on bad input.
	static std::shared_ptr<Graph> smiles(const std::string &smiles);
	// rst: .. function:: static std::shared_ptr<Graph> makeGraph(std::unique_ptr<lib::Graph::Single> g)
	// rst:               static std::shared_ptr<Graph> makeGraph(std::unique_ptr<lib::Graph::Single> g, std::map<int, std::size_t> externalToInternalIds)
	// rst:
	// rst:		:returns: a graph wrapping the given internal graph object. If an id mapping is given, it will be used for the :cpp:func:`getVertexFromExternalId` function.
	static std::shared_ptr<Graph> makeGraph(std::unique_ptr<lib::Graph::Single> g);
	static std::shared_ptr<Graph> makeGraph(std::unique_ptr<lib::Graph::Single> g, std::map<int, std::size_t> externalToInternalIds);
};
// rst-class-end:

struct GraphLess {

	bool operator()(std::shared_ptr<Graph> g1, std::shared_ptr<Graph> g2) const {
		return g1->getId() < g2->getId();
	}
};

} // namespace mod

#endif /* MOD_GRAPH_H */
