/* SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright 2005 Blender Foundation. All rights reserved. */

/** \file
 * \ingroup texnodes
 */

#include "NOD_texture.h"
#include "node_texture_util.hh"

static bNodeSocketTemplate outputs[] = {
    {SOCK_VECTOR, N_("Coordinates")},
    {-1, ""},
};

static void vectorfn(
    float *out, TexParams *p, bNode * /*node*/, bNodeStack ** /*in*/, short /*thread*/)
{
  copy_v3_v3(out, p->co);
}

static void exec(void *data,
                 int /*thread*/,
                 bNode *node,
                 bNodeExecData *execdata,
                 bNodeStack **in,
                 bNodeStack **out)
{
  tex_output(node, execdata, in, out[0], &vectorfn, static_cast<TexCallData *>(data));
}

void register_node_type_tex_coord(void)
{
  static bNodeType ntype;

  tex_node_type_base(&ntype, TEX_NODE_COORD, "Coordinates", NODE_CLASS_INPUT);
  node_type_socket_templates(&ntype, nullptr, outputs);
  ntype.exec_fn = exec;

  nodeRegisterType(&ntype);
}
