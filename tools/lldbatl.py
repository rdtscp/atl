import lldb
import lldb.formatters.Logger

class atlvector_SynthProvider:

    def __init__(self, valobj, dict):
        self.valobj = valobj
        self.update()

    def num_children(self):
        num_elems = self.elements_used.GetValueAsUnsigned()
        return num_elems

    def get_child_index(self, name):
        return int(name.lstrip('[').rstrip(']'))

    def get_child_at_index(self, index):
        if index < 0 or index >= self.num_children():
            return None
        offset = index * self.data_size
        return self.elements.CreateChildAtOffset('[' + str(index) + ']', offset, self.data_type)

    def get_type_from_name(self):
        import re
        name = self.valobj.GetType().GetName()
        res = re.match("^(atl::)?vector<(.+)>$", name)
        if res:
            return res.group(2)
        res = re.match("^(atl::)?vector<(.+), \d+>$", name)
        if res:
            return res.group(2)
        return None

    def update(self):
        self.elements = self.valobj.GetChildMemberWithName('elements')
        self.elements_used = self.valobj.GetChildMemberWithName('elements_used')
        self.data_type = self.elements.GetType().GetPointeeType()
        self.data_size = self.data_type.GetByteSize()

    def has_children(self):
        return True


def atlvector_SummaryProvider(valobj, dict):
    return "size={}".format(valobj.GetNumChildren())

def __lldb_init_module(debugger, dict):
    debugger.HandleCommand('type summary add -F'
                           'libatl.atlvector_SummaryProvider -e -x "^atl::vector<.+>$"')
    debugger.HandleCommand('type synthetic add -l'
                           'libatl.atlvector_SynthProvider -x "^atl::vector<.+>$"')