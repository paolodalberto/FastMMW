static PyObject* s_dcmulP(PyObject *self, PyObject *args);
static PyObject* s_mulP(PyObject *self, PyObject *args);
static PyObject* s_mulptP(PyObject *self, PyObject *args);
static PyObject* s_maddP(PyObject *self, PyObject *args);
static PyObject* s_saddmulP(PyObject *self, PyObject *args);
static PyObject* s_smulP(PyObject *self, PyObject *args);
static PyObject* s_saddmulRP(PyObject *self, PyObject *args);
static PyObject* s_smulRP(PyObject *self, PyObject *args);
static PyObject* s_wmulP(PyObject *self, PyObject *args);
static PyObject* s_waddmulP(PyObject *self, PyObject *args);
static PyObject* s_wmP(PyObject *self, PyObject *args);
static PyObject* s_wmaddP(PyObject *self, PyObject *args);
static PyObject* s_wmRP(PyObject *self, PyObject *args);
static PyObject* s_wmaddRP(PyObject *self, PyObject *args);
static PyObject* s_wmTRP(PyObject *self, PyObject *args);
static PyObject* s_wmaddTRP(PyObject *self, PyObject *args);
static PyObject* s_adaptive_smulP(PyObject *self, PyObject *args);
static PyObject* s_omulP(PyObject *self, PyObject *args);
static PyObject* s_oaddmulP(PyObject *self, PyObject *args);
static PyObject* s_owmulP(PyObject *self, PyObject *args);
static PyObject* s_owaddmulP(PyObject *self, PyObject *args);
static PyObject* s_bmP(PyObject *self, PyObject *args);
static PyObject* s_bmaddP(PyObject *self, PyObject *args);
static PyObject* s_ptaddmulP(PyObject *self, PyObject *args);
static PyObject* s_wmpipeP(PyObject *self, PyObject *args);
static PyObject* s_wmaddpipeP(PyObject *self, PyObject *args);
static PyObject* s_bmpipeP(PyObject *self, PyObject *args);
static PyObject* s_bmaddpipeP(PyObject *self, PyObject *args);
static PyObject* s_smpipeP(PyObject *self, PyObject *args);
static PyObject* s_smaddpipeP(PyObject *self, PyObject *args);
static PyObject* s_RmulP(PyObject *self, PyObject *args);
static PyObject* s_adaptive_wmP(PyObject *self, PyObject *args);
static PyObject* s_BMADD_PIPEP(PyObject *self, PyObject *args);
static PyObject* s_BMADDP(PyObject *self, PyObject *args);
static PyObject* s_BMADDRP(PyObject *self, PyObject *args);
static PyObject* s_BMOWR_PIPEP(PyObject *self, PyObject *args);
static PyObject* s_BMOWRP(PyObject *self, PyObject *args);
static PyObject* s_BMOWRRP(PyObject *self, PyObject *args);
static PyObject* d_dcmulP(PyObject *self, PyObject *args);
static PyObject* d_mulP(PyObject *self, PyObject *args);
static PyObject* d_mulptP(PyObject *self, PyObject *args);
static PyObject* d_maddP(PyObject *self, PyObject *args);
static PyObject* d_saddmulP(PyObject *self, PyObject *args);
static PyObject* d_smulP(PyObject *self, PyObject *args);
static PyObject* d_saddmulRP(PyObject *self, PyObject *args);
static PyObject* d_smulRP(PyObject *self, PyObject *args);
static PyObject* d_wmulP(PyObject *self, PyObject *args);
static PyObject* d_waddmulP(PyObject *self, PyObject *args);
static PyObject* d_wmP(PyObject *self, PyObject *args);
static PyObject* d_wmaddP(PyObject *self, PyObject *args);
static PyObject* d_wmRP(PyObject *self, PyObject *args);
static PyObject* d_wmaddRP(PyObject *self, PyObject *args);
static PyObject* d_wmTRP(PyObject *self, PyObject *args);
static PyObject* d_wmaddTRP(PyObject *self, PyObject *args);
static PyObject* d_adaptive_smulP(PyObject *self, PyObject *args);
static PyObject* d_omulP(PyObject *self, PyObject *args);
static PyObject* d_oaddmulP(PyObject *self, PyObject *args);
static PyObject* d_owmulP(PyObject *self, PyObject *args);
static PyObject* d_owaddmulP(PyObject *self, PyObject *args);
static PyObject* d_bmP(PyObject *self, PyObject *args);
static PyObject* d_bmaddP(PyObject *self, PyObject *args);
static PyObject* d_ptaddmulP(PyObject *self, PyObject *args);
static PyObject* d_wmpipeP(PyObject *self, PyObject *args);
static PyObject* d_wmaddpipeP(PyObject *self, PyObject *args);
static PyObject* d_bmpipeP(PyObject *self, PyObject *args);
static PyObject* d_bmaddpipeP(PyObject *self, PyObject *args);
static PyObject* d_smpipeP(PyObject *self, PyObject *args);
static PyObject* d_smaddpipeP(PyObject *self, PyObject *args);
static PyObject* d_RmulP(PyObject *self, PyObject *args);
static PyObject* d_adaptive_wmP(PyObject *self, PyObject *args);
static PyObject* d_BMADD_PIPEP(PyObject *self, PyObject *args);
static PyObject* d_BMADDP(PyObject *self, PyObject *args);
static PyObject* d_BMADDRP(PyObject *self, PyObject *args);
static PyObject* d_BMOWR_PIPEP(PyObject *self, PyObject *args);
static PyObject* d_BMOWRP(PyObject *self, PyObject *args);
static PyObject* d_BMOWRRP(PyObject *self, PyObject *args);
static PyObject* c_dcmulP(PyObject *self, PyObject *args);
static PyObject* c_mulP(PyObject *self, PyObject *args);
static PyObject* c_mulptP(PyObject *self, PyObject *args);
static PyObject* c_maddP(PyObject *self, PyObject *args);
static PyObject* c_saddmulP(PyObject *self, PyObject *args);
static PyObject* c_smulP(PyObject *self, PyObject *args);
static PyObject* c_saddmulRP(PyObject *self, PyObject *args);
static PyObject* c_smulRP(PyObject *self, PyObject *args);
static PyObject* c_wmulP(PyObject *self, PyObject *args);
static PyObject* c_waddmulP(PyObject *self, PyObject *args);
static PyObject* c_wmP(PyObject *self, PyObject *args);
static PyObject* c_wmaddP(PyObject *self, PyObject *args);
static PyObject* c_wmRP(PyObject *self, PyObject *args);
static PyObject* c_wmaddRP(PyObject *self, PyObject *args);
static PyObject* c_wmTRP(PyObject *self, PyObject *args);
static PyObject* c_wmaddTRP(PyObject *self, PyObject *args);
static PyObject* c_adaptive_smulP(PyObject *self, PyObject *args);
static PyObject* c_omulP(PyObject *self, PyObject *args);
static PyObject* c_oaddmulP(PyObject *self, PyObject *args);
static PyObject* c_owmulP(PyObject *self, PyObject *args);
static PyObject* c_owaddmulP(PyObject *self, PyObject *args);
static PyObject* c_bmP(PyObject *self, PyObject *args);
static PyObject* c_bmaddP(PyObject *self, PyObject *args);
static PyObject* c_ptaddmulP(PyObject *self, PyObject *args);
static PyObject* c_wmpipeP(PyObject *self, PyObject *args);
static PyObject* c_wmaddpipeP(PyObject *self, PyObject *args);
static PyObject* c_bmpipeP(PyObject *self, PyObject *args);
static PyObject* c_bmaddpipeP(PyObject *self, PyObject *args);
static PyObject* c_smpipeP(PyObject *self, PyObject *args);
static PyObject* c_smaddpipeP(PyObject *self, PyObject *args);
static PyObject* c_RmulP(PyObject *self, PyObject *args);
static PyObject* c_adaptive_wmP(PyObject *self, PyObject *args);
static PyObject* c_BMADD_PIPEP(PyObject *self, PyObject *args);
static PyObject* c_BMADDP(PyObject *self, PyObject *args);
static PyObject* c_BMADDRP(PyObject *self, PyObject *args);
static PyObject* c_BMOWR_PIPEP(PyObject *self, PyObject *args);
static PyObject* c_BMOWRP(PyObject *self, PyObject *args);
static PyObject* c_BMOWRRP(PyObject *self, PyObject *args);
static PyObject* z_dcmulP(PyObject *self, PyObject *args);
static PyObject* z_mulP(PyObject *self, PyObject *args);
static PyObject* z_mulptP(PyObject *self, PyObject *args);
static PyObject* z_maddP(PyObject *self, PyObject *args);
static PyObject* z_saddmulP(PyObject *self, PyObject *args);
static PyObject* z_smulP(PyObject *self, PyObject *args);
static PyObject* z_saddmulRP(PyObject *self, PyObject *args);
static PyObject* z_smulRP(PyObject *self, PyObject *args);
static PyObject* z_wmulP(PyObject *self, PyObject *args);
static PyObject* z_waddmulP(PyObject *self, PyObject *args);
static PyObject* z_wmP(PyObject *self, PyObject *args);
static PyObject* z_wmaddP(PyObject *self, PyObject *args);
static PyObject* z_wmRP(PyObject *self, PyObject *args);
static PyObject* z_wmaddRP(PyObject *self, PyObject *args);
static PyObject* z_wmTRP(PyObject *self, PyObject *args);
static PyObject* z_wmaddTRP(PyObject *self, PyObject *args);
static PyObject* z_adaptive_smulP(PyObject *self, PyObject *args);
static PyObject* z_omulP(PyObject *self, PyObject *args);
static PyObject* z_oaddmulP(PyObject *self, PyObject *args);
static PyObject* z_owmulP(PyObject *self, PyObject *args);
static PyObject* z_owaddmulP(PyObject *self, PyObject *args);
static PyObject* z_bmP(PyObject *self, PyObject *args);
static PyObject* z_bmaddP(PyObject *self, PyObject *args);
static PyObject* z_ptaddmulP(PyObject *self, PyObject *args);
static PyObject* z_wmpipeP(PyObject *self, PyObject *args);
static PyObject* z_wmaddpipeP(PyObject *self, PyObject *args);
static PyObject* z_bmpipeP(PyObject *self, PyObject *args);
static PyObject* z_bmaddpipeP(PyObject *self, PyObject *args);
static PyObject* z_smpipeP(PyObject *self, PyObject *args);
static PyObject* z_smaddpipeP(PyObject *self, PyObject *args);
static PyObject* z_RmulP(PyObject *self, PyObject *args);
static PyObject* z_adaptive_wmP(PyObject *self, PyObject *args);
static PyObject* z_BMADD_PIPEP(PyObject *self, PyObject *args);
static PyObject* z_BMADDP(PyObject *self, PyObject *args);
static PyObject* z_BMADDRP(PyObject *self, PyObject *args);
static PyObject* z_BMOWR_PIPEP(PyObject *self, PyObject *args);
static PyObject* z_BMOWRP(PyObject *self, PyObject *args);
static PyObject* z_BMOWRRP(PyObject *self, PyObject *args);
static PyObject* s_mm_leaf_computation_maddP(PyObject *self, PyObject *args);
static PyObject* s_mm_leaf_computationP(PyObject *self, PyObject *args);
static PyObject* d_mm_leaf_computation_maddP(PyObject *self, PyObject *args);
static PyObject* d_mm_leaf_computationP(PyObject *self, PyObject *args);
static PyObject* c_mm_leaf_computation_maddP(PyObject *self, PyObject *args);
static PyObject* c_mm_leaf_computationP(PyObject *self, PyObject *args);
static PyObject* z_mm_leaf_computation_maddP(PyObject *self, PyObject *args);
static PyObject* z_mm_leaf_computationP(PyObject *self, PyObject *args);
static PyMethodDef FMMWPMethods[] = {
{"s_dcmulP", s_dcmulP, METH_VARARGS},
{"s_mulP", s_mulP, METH_VARARGS},
{"s_mulptP", s_mulptP, METH_VARARGS},
{"s_maddP", s_maddP, METH_VARARGS},
{"s_saddmulP", s_saddmulP, METH_VARARGS},
{"s_smulP", s_smulP, METH_VARARGS},
{"s_saddmulRP", s_saddmulRP, METH_VARARGS},
{"s_smulRP", s_smulRP, METH_VARARGS},
{"s_wmulP", s_wmulP, METH_VARARGS},
{"s_waddmulP", s_waddmulP, METH_VARARGS},
{"s_wmP", s_wmP, METH_VARARGS},
{"s_wmaddP", s_wmaddP, METH_VARARGS},
{"s_wmRP", s_wmRP, METH_VARARGS},
{"s_wmaddRP", s_wmaddRP, METH_VARARGS},
{"s_wmTRP", s_wmTRP, METH_VARARGS},
{"s_wmaddTRP", s_wmaddTRP, METH_VARARGS},
{"s_adaptive_smulP", s_adaptive_smulP, METH_VARARGS},
{"s_omulP", s_omulP, METH_VARARGS},
{"s_oaddmulP", s_oaddmulP, METH_VARARGS},
{"s_owmulP", s_owmulP, METH_VARARGS},
{"s_owaddmulP", s_owaddmulP, METH_VARARGS},
{"s_bmP", s_bmP, METH_VARARGS},
{"s_bmaddP", s_bmaddP, METH_VARARGS},
{"s_ptaddmulP", s_ptaddmulP, METH_VARARGS},
{"s_wmpipeP", s_wmpipeP, METH_VARARGS},
{"s_wmaddpipeP", s_wmaddpipeP, METH_VARARGS},
{"s_bmpipeP", s_bmpipeP, METH_VARARGS},
{"s_bmaddpipeP", s_bmaddpipeP, METH_VARARGS},
{"s_smpipeP", s_smpipeP, METH_VARARGS},
{"s_smaddpipeP", s_smaddpipeP, METH_VARARGS},
{"s_RmulP", s_RmulP, METH_VARARGS},
{"s_adaptive_wmP", s_adaptive_wmP, METH_VARARGS},
{"s_BMADD_PIPEP", s_BMADD_PIPEP, METH_VARARGS},
{"s_BMADDP", s_BMADDP, METH_VARARGS},
{"s_BMADDRP", s_BMADDRP, METH_VARARGS},
{"s_BMOWR_PIPEP", s_BMOWR_PIPEP, METH_VARARGS},
{"s_BMOWRP", s_BMOWRP, METH_VARARGS},
{"s_BMOWRRP", s_BMOWRRP, METH_VARARGS},
{"d_dcmulP", d_dcmulP, METH_VARARGS},
{"d_mulP", d_mulP, METH_VARARGS},
{"d_mulptP", d_mulptP, METH_VARARGS},
{"d_maddP", d_maddP, METH_VARARGS},
{"d_saddmulP", d_saddmulP, METH_VARARGS},
{"d_smulP", d_smulP, METH_VARARGS},
{"d_saddmulRP", d_saddmulRP, METH_VARARGS},
{"d_smulRP", d_smulRP, METH_VARARGS},
{"d_wmulP", d_wmulP, METH_VARARGS},
{"d_waddmulP", d_waddmulP, METH_VARARGS},
{"d_wmP", d_wmP, METH_VARARGS},
{"d_wmaddP", d_wmaddP, METH_VARARGS},
{"d_wmRP", d_wmRP, METH_VARARGS},
{"d_wmaddRP", d_wmaddRP, METH_VARARGS},
{"d_wmTRP", d_wmTRP, METH_VARARGS},
{"d_wmaddTRP", d_wmaddTRP, METH_VARARGS},
{"d_adaptive_smulP", d_adaptive_smulP, METH_VARARGS},
{"d_omulP", d_omulP, METH_VARARGS},
{"d_oaddmulP", d_oaddmulP, METH_VARARGS},
{"d_owmulP", d_owmulP, METH_VARARGS},
{"d_owaddmulP", d_owaddmulP, METH_VARARGS},
{"d_bmP", d_bmP, METH_VARARGS},
{"d_bmaddP", d_bmaddP, METH_VARARGS},
{"d_ptaddmulP", d_ptaddmulP, METH_VARARGS},
{"d_wmpipeP", d_wmpipeP, METH_VARARGS},
{"d_wmaddpipeP", d_wmaddpipeP, METH_VARARGS},
{"d_bmpipeP", d_bmpipeP, METH_VARARGS},
{"d_bmaddpipeP", d_bmaddpipeP, METH_VARARGS},
{"d_smpipeP", d_smpipeP, METH_VARARGS},
{"d_smaddpipeP", d_smaddpipeP, METH_VARARGS},
{"d_RmulP", d_RmulP, METH_VARARGS},
{"d_adaptive_wmP", d_adaptive_wmP, METH_VARARGS},
{"d_BMADD_PIPEP", d_BMADD_PIPEP, METH_VARARGS},
{"d_BMADDP", d_BMADDP, METH_VARARGS},
{"d_BMADDRP", d_BMADDRP, METH_VARARGS},
{"d_BMOWR_PIPEP", d_BMOWR_PIPEP, METH_VARARGS},
{"d_BMOWRP", d_BMOWRP, METH_VARARGS},
{"d_BMOWRRP", d_BMOWRRP, METH_VARARGS},
{"c_dcmulP", c_dcmulP, METH_VARARGS},
{"c_mulP", c_mulP, METH_VARARGS},
{"c_mulptP", c_mulptP, METH_VARARGS},
{"c_maddP", c_maddP, METH_VARARGS},
{"c_saddmulP", c_saddmulP, METH_VARARGS},
{"c_smulP", c_smulP, METH_VARARGS},
{"c_saddmulRP", c_saddmulRP, METH_VARARGS},
{"c_smulRP", c_smulRP, METH_VARARGS},
{"c_wmulP", c_wmulP, METH_VARARGS},
{"c_waddmulP", c_waddmulP, METH_VARARGS},
{"c_wmP", c_wmP, METH_VARARGS},
{"c_wmaddP", c_wmaddP, METH_VARARGS},
{"c_wmRP", c_wmRP, METH_VARARGS},
{"c_wmaddRP", c_wmaddRP, METH_VARARGS},
{"c_wmTRP", c_wmTRP, METH_VARARGS},
{"c_wmaddTRP", c_wmaddTRP, METH_VARARGS},
{"c_adaptive_smulP", c_adaptive_smulP, METH_VARARGS},
{"c_omulP", c_omulP, METH_VARARGS},
{"c_oaddmulP", c_oaddmulP, METH_VARARGS},
{"c_owmulP", c_owmulP, METH_VARARGS},
{"c_owaddmulP", c_owaddmulP, METH_VARARGS},
{"c_bmP", c_bmP, METH_VARARGS},
{"c_bmaddP", c_bmaddP, METH_VARARGS},
{"c_ptaddmulP", c_ptaddmulP, METH_VARARGS},
{"c_wmpipeP", c_wmpipeP, METH_VARARGS},
{"c_wmaddpipeP", c_wmaddpipeP, METH_VARARGS},
{"c_bmpipeP", c_bmpipeP, METH_VARARGS},
{"c_bmaddpipeP", c_bmaddpipeP, METH_VARARGS},
{"c_smpipeP", c_smpipeP, METH_VARARGS},
{"c_smaddpipeP", c_smaddpipeP, METH_VARARGS},
{"c_RmulP", c_RmulP, METH_VARARGS},
{"c_adaptive_wmP", c_adaptive_wmP, METH_VARARGS},
{"c_BMADD_PIPEP", c_BMADD_PIPEP, METH_VARARGS},
{"c_BMADDP", c_BMADDP, METH_VARARGS},
{"c_BMADDRP", c_BMADDRP, METH_VARARGS},
{"c_BMOWR_PIPEP", c_BMOWR_PIPEP, METH_VARARGS},
{"c_BMOWRP", c_BMOWRP, METH_VARARGS},
{"c_BMOWRRP", c_BMOWRRP, METH_VARARGS},
{"z_dcmulP", z_dcmulP, METH_VARARGS},
{"z_mulP", z_mulP, METH_VARARGS},
{"z_mulptP", z_mulptP, METH_VARARGS},
{"z_maddP", z_maddP, METH_VARARGS},
{"z_saddmulP", z_saddmulP, METH_VARARGS},
{"z_smulP", z_smulP, METH_VARARGS},
{"z_saddmulRP", z_saddmulRP, METH_VARARGS},
{"z_smulRP", z_smulRP, METH_VARARGS},
{"z_wmulP", z_wmulP, METH_VARARGS},
{"z_waddmulP", z_waddmulP, METH_VARARGS},
{"z_wmP", z_wmP, METH_VARARGS},
{"z_wmaddP", z_wmaddP, METH_VARARGS},
{"z_wmRP", z_wmRP, METH_VARARGS},
{"z_wmaddRP", z_wmaddRP, METH_VARARGS},
{"z_wmTRP", z_wmTRP, METH_VARARGS},
{"z_wmaddTRP", z_wmaddTRP, METH_VARARGS},
{"z_adaptive_smulP", z_adaptive_smulP, METH_VARARGS},
{"z_omulP", z_omulP, METH_VARARGS},
{"z_oaddmulP", z_oaddmulP, METH_VARARGS},
{"z_owmulP", z_owmulP, METH_VARARGS},
{"z_owaddmulP", z_owaddmulP, METH_VARARGS},
{"z_bmP", z_bmP, METH_VARARGS},
{"z_bmaddP", z_bmaddP, METH_VARARGS},
{"z_ptaddmulP", z_ptaddmulP, METH_VARARGS},
{"z_wmpipeP", z_wmpipeP, METH_VARARGS},
{"z_wmaddpipeP", z_wmaddpipeP, METH_VARARGS},
{"z_bmpipeP", z_bmpipeP, METH_VARARGS},
{"z_bmaddpipeP", z_bmaddpipeP, METH_VARARGS},
{"z_smpipeP", z_smpipeP, METH_VARARGS},
{"z_smaddpipeP", z_smaddpipeP, METH_VARARGS},
{"z_RmulP", z_RmulP, METH_VARARGS},
{"z_adaptive_wmP", z_adaptive_wmP, METH_VARARGS},
{"z_BMADD_PIPEP", z_BMADD_PIPEP, METH_VARARGS},
{"z_BMADDP", z_BMADDP, METH_VARARGS},
{"z_BMADDRP", z_BMADDRP, METH_VARARGS},
{"z_BMOWR_PIPEP", z_BMOWR_PIPEP, METH_VARARGS},
{"z_BMOWRP", z_BMOWRP, METH_VARARGS},
{"z_BMOWRRP", z_BMOWRRP, METH_VARARGS},
{"s_mm_leaf_computation_maddP", s_mm_leaf_computation_maddP, METH_VARARGS},
{"s_mm_leaf_computationP", s_mm_leaf_computationP, METH_VARARGS},
{"d_mm_leaf_computation_maddP", d_mm_leaf_computation_maddP, METH_VARARGS},
{"d_mm_leaf_computationP", d_mm_leaf_computationP, METH_VARARGS},
{"c_mm_leaf_computation_maddP", c_mm_leaf_computation_maddP, METH_VARARGS},
{"c_mm_leaf_computationP", c_mm_leaf_computationP, METH_VARARGS},
{"z_mm_leaf_computation_maddP", z_mm_leaf_computation_maddP, METH_VARARGS},
{"z_mm_leaf_computationP", z_mm_leaf_computationP, METH_VARARGS},
{NULL,NULL}
};
