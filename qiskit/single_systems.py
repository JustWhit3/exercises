from qiskit.quantum_info import Statevector, Operator
from qiskit.visualization import plot_histogram, circuit_drawer
from qiskit import QuantumCircuit
import numpy as np

if __name__ == "__main__":
    
    # Basic state vectors
    print("Basic state vectors")
    sv = Statevector([1/np.sqrt(2), 1/np.sqrt(2)])
    print(sv.is_valid())
    print(sv.measure(), end="\n\n")
    
    uv = Statevector([(1+2j)/3, -2/3])
    print(uv)
    print(uv.measure(), end="\n\n")
    
    # Plotting probability
    print("Plotting probability")
    statistics = uv.sample_counts(1000)
    print(statistics, end="\n\n")
    histo = plot_histogram(statistics)
    histo.savefig("img/statistics.png")
    
    # Operations
    print("Operators")
    O = Operator([[0, 1], [1, 0]])
    print(O)
    print(sv.evolve(O), end="\n\n")
    
    # Quantum circuit basis
    circuit = QuantumCircuit(1)
    circuit.h(0)
    circuit.t(0)
    circuit.h(0)
    circuit.t(0)
    circuit.z(0)
    circuit_drawer(circuit, output="mpl", filename="img/circuit.png")
    print(sv.evolve(circuit))
    statistics = sv.evolve(circuit).sample_counts(4000)
    histo = plot_histogram(statistics)
    histo.savefig("img/statistics_circuit.png")
    