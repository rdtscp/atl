def atlsharedprtr_SummaryProvider(valobj, dict_env):
    ptr = valobj.GetChildMemberWithName('ptr')

    type_name = ptr.GetTypeName()
    if type_name == None:
        return "nullptr"
    return "<{}>".format(type_name).replace(" *", "")


class atlshared_ptr_SynthProvider:

    def __init__(self, valobj, dict_env):
        self.valobj = valobj
        self.update()

    def num_children(self):
        return 1

    def get_child_index(self, name):
        return 0

    def get_child_at_index(self, index):
        if self.m_ptr.GetValue() != "0x0000000000000000":
            return self.m_ptr
        else:
            return None

    def get_type_from_name(self):
        import re
        name = self.valobj.GetType().GetName()
        res = re.match("^(atl::)?shared_ptr<(.+)>$", name)
        if res:
            return res.group(2)
        return None

    def update(self):
        self.m_ptr = self.valobj.GetChildMemberWithName('m_ptr')

    def has_children(self):
        return True


def atlstring_SummaryProvider(valobj, dict_env):
    m_value = valobj.GetChildMemberWithName('m_value').GetSummary()
    if len(m_value) > 25:
        m_value = "\"[...]" + m_value[-25:]
    return m_value


class atlvector_SynthProvider:

    def __init__(self, valobj, dict_env):
        self.valobj = valobj
        self.update()

    def num_children(self):
        num_elems = self.m_elements_used.GetValueAsUnsigned()
        return num_elems

    def get_child_index(self, name):
        return int(name.lstrip('[').rstrip(']'))

    def get_child_at_index(self, index):
        if index < 0 or index >= self.num_children():
            return None
        offset = index * self.data_size
        return self.m_elements.CreateChildAtOffset('[' + str(index) + ']', offset, self.data_type)

    def get_type_from_name(self):
        import re
        name = self.valobj.GetType().GetName()
        res = re.match("^(atl::)?vector<(.+)>$", name)
        if res:
            return res.group(2)
        return None

    def update(self):
        self.m_elements = self.valobj.GetChildMemberWithName('m_elements')
        self.m_elements_used = self.valobj.GetChildMemberWithName('m_elements_used')
        self.data_type = self.m_elements.GetType().GetPointeeType()
        self.data_size = self.data_type.GetByteSize()

    def has_children(self):
        return True


def atlvector_SummaryProvider(valobj, dict_env):
    return "size={}".format(valobj.GetNumChildren())


def __lldb_init_module(debugger, dict_env):
    debugger.HandleCommand('type summary add -F'
                           'lldbatl.atlvector_SummaryProvider -e -x "^atl::set<.+>$"')
    debugger.HandleCommand('type synthetic add -l'
                           'lldbatl.atlvector_SynthProvider -x "^atl::set<.+>$"')
    debugger.HandleCommand('type summary add -F'
                           'lldbatl.atlsharedprtr_SummaryProvider -e -x "^atl::shared_ptr<.+>$"')
    debugger.HandleCommand('type synthetic add -l'
                           'lldbatl.atlshared_ptr_SynthProvider -x "^atl::shared_ptr<.+>$"')
    debugger.HandleCommand('type summary add -F'
                           'lldbatl.atlstring_SummaryProvider -x "^atl::string$"')
    debugger.HandleCommand('type summary add -F'
                           'lldbatl.atlvector_SummaryProvider -e -x "^atl::vector<.+>$"')
    debugger.HandleCommand('type synthetic add -l'
                           'lldbatl.atlvector_SynthProvider -x "^atl::vector<.+>$"')
    # Prevent Debugger from Stepping into atl.
    debugger.HandleCommand('settings set target.process.thread.step-avoid-regexp ^(atl::)')