import os
import glob
import unittest
import ddt
import difflib
import subprocess

def make_test_data():
    class my_list( list ):
        pass
    base_dir = os.path.dirname( __file__ )
    bin_dir = os.path.join( base_dir, '.out' )
    data_dir = os.path.join( base_dir, 'test_data' )
    
    input_dir = os.path.join( data_dir, 'input' )
    output_dir = os.path.join( data_dir, 'output' )
    expected_dir = os.path.join( data_dir, 'expected' )
    
    test_data = []
    for module_file in glob.glob( os.path.join( bin_dir, '*.exe' ) ):
        module_name = os.path.splitext( os.path.basename( module_file ) )[0]
        input_files = (
            glob.glob( os.path.join( input_dir, module_name + '.txt' ) ) +
            glob.glob( os.path.join( input_dir, module_name + '?[0-9]*.txt' ) )
            )
        for input_file in input_files:
        #for input_file in glob.glob( os.path.join( input_dir, module_name + '?[0-9].txt' ) ):
            input_file_name = os.path.basename( input_file )
            expected_file = os.path.join( expected_dir, input_file_name )
            output_file = os.path.join( output_dir, input_file_name )
            data = my_list( [ module_file, { 'input': input_file, 'output': output_file, 'expected': expected_file } ] )
            data.__name__ = "test_%(module)s_%(input)s" % dict(
                module = module_name,
                input = os.path.splitext( input_file_name )[0]
                )
            test_data.append( data )
    return test_data

@ddt.ddt
class test_ctci( unittest.TestCase ):
    
    @ddt.data( *make_test_data() )
    @ddt.unpack
    def test( self, module, data ):
        output_dir = os.path.dirname( data['output'] )
        if not os.path.exists( output_dir ):
            os.makedirs( output_dir )
        with open( data['input'], 'rU' ) as input_file:
            with open( data['output'], 'w' ) as output_file:
                # print '\nRunning %s with %s...' % ( module, input_file )
                p = subprocess.Popen( module, stdin = input_file, stdout = output_file )
                p.wait()
                output_file.flush()

        with open( data['output'], 'rU' ) as output_file:
            with open( data['expected'], 'rU' ) as expected_file:
                expected = expected_file.read().splitlines( False )
                output = output_file.read().splitlines( False )
                diff = list( difflib.context_diff( output, expected ) )
                self.assertEqual( diff, [], '''Files are different:
output:   %s
expected: %s
''' % ( data['output'], data['expected'] ) )

if __name__ == '__main__':
    unittest.main()
